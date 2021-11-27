/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-kass <ael-kass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 16:30:35 by ael-kass          #+#    #+#             */
/*   Updated: 2021/11/27 20:59:03 by ael-kass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long		get_time(struct timeval	tv)
{
	struct timeval	tv1;
	long			time;

	gettimeofday(&tv1, NULL);
	time = ((tv1.tv_sec * 1000) + (tv1.tv_usec / 1000)) 
		- ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
	return (time);
}

void	print_death(arguments_t **args, long time, int i)
{
	pthread_mutex_lock((*args)[i].display);
	printf("%ld %d died\n", time, (*args)[i].philo_id);
}

void	print_actions(arguments_t *args, char *str)
{
		pthread_mutex_lock(args->display);
		printf("%ld %d %s\n", get_time(args->start_simulation), args->philo_id + 1, str);
		pthread_mutex_unlock(args->display);
}

void	usleep_(useconds_t usec)
{
	struct  timeval tv1;

	
	gettimeofday(&tv1, NULL);
	usleep(usec - 20000);
	while (get_time(tv1) * 1000 < usec)
	{
	}
}

void	*routine(void *args)
{
  	arguments_t		*args1;

	args1 = (arguments_t *)args;
	if (args1->philo_id % 2)
		usleep(400);
	while (1)
	{
		pthread_mutex_lock(&args1->mutex[args1->philo_id]);
		//printf("%ld %d has taken a fork\n", get_time(args1->start_simulation), args1->philo_id + 1);
		print_actions(args1, "has taken a fork");
		pthread_mutex_lock(&args1->mutex[(args1->philo_id + 1) % args1->num_philo]);
		//printf("%ld %d has taken a fork\n", get_time(args1->start_simulation), args1->philo_id + 1);
		print_actions(args1, "has taken a fork");
		//////////start eating and unlock ////////////

		args1->eating = 1;

		pthread_mutex_lock(&args1->m_eat[args1->philo_id]);



		args1->time = get_time(args1->start_simulation);
		// printf("%zu %d is eating\n", get_time(args1->start_simulation), args1->philo_id + 1);
		print_actions(args1, "is eating");
		usleep_(args1->t_eat * 1000);
		pthread_mutex_unlock(&args1->mutex[args1->philo_id]);
		pthread_mutex_unlock(&args1->mutex[(args1->philo_id + 1) % args1->num_philo]);


		pthread_mutex_unlock(&args1->m_eat[args1->philo_id]);

		args1->eating = 0;

		// start sleeping /////////
		// printf("%zu %d is sleeping\n", get_time(args1->start_simulation), args1->philo_id + 1);
		print_actions(args1, "is sleeping");
		usleep_(args1->t_sleep * 1000);
		// start thinking ////////////
		//printf("%zu %d is thinking\n", get_time(args1->start_simulation), args1->philo_id + 1);
		print_actions(args1, "is thinking");
		/// start when end /////
		//printf("philo %d, last_time = %d\n",args1->philo_id + 1, (tv.tv_usec - time) / 1000);
	}
}

void	creat_threads(arguments_t **args)
{
	pthread_t			*th;
	int					i;
	struct timeval		time;

	th = (pthread_t *)malloc((*args)->num_philo * sizeof(pthread_t));
	gettimeofday(&time, NULL);
	i = -1;
	while (++i < (*args)->num_philo)
	{
		(*args)[i].start_simulation = time;
		if (pthread_create(th + i, NULL, &routine, &(*args)[i]))
		{
			printf("Error\n");
			return ;
		}
	}
	i = -1;
	while (++i < (*args)->num_philo)
	{
		if (pthread_mutex_destroy(&(*args)->mutex[i]))
		{
			printf("Error\n");
			return ;
		}
	}
}

void	parsing(int len, char **argv, arguments_t **args)
{
	if (len > 5 || len < 4)
		print_error();
	(*args)->num_philo = ft_atoi(argv[1]);
	if ((*args)->num_philo <= 0)
        print_error();
	(*args)->t_die = ft_atoi(argv[2]);
	(*args)->t_eat = ft_atoi(argv[3]);
	(*args)->t_sleep = ft_atoi(argv[4]);
	if ((*args)->t_die < 0 || (*args)->t_eat < 0 || (*args)->t_sleep < 0)
		print_error();
	if (len == 5)
	{
		(*args)->num_t_philo = ft_atoi(argv[5]);
		if ((*args)->num_t_philo < 0)
			print_error();
	}
}

int	main(int argc, char *argv[])
{
   // pthread_t			t1;
	arguments_t			*args_temp;
	arguments_t			*args;
	pthread_mutex_t		*mutex;
	pthread_mutex_t		*eat;
	pthread_mutex_t		display;
	struct timeval		tv;
	int					i;

	args_temp = (arguments_t *)malloc(sizeof(arguments_t));
	parsing(argc - 1, argv, &args_temp);
	mutex = (pthread_mutex_t *)malloc(args_temp->num_philo * sizeof(pthread_mutex_t));
	eat = (pthread_mutex_t *)malloc(args_temp->num_philo * sizeof(pthread_mutex_t));
	pthread_mutex_init(&display, NULL);
	args = (arguments_t *)malloc(args_temp->num_philo * sizeof(arguments_t));
	i = -1;
	while (++i < args_temp->num_philo)
	{
		if (pthread_mutex_init(&mutex[i], NULL))
		{
			printf("Error\n");
			return 0;
		} 
		if (pthread_mutex_init(&eat[i], NULL))
		{
			printf("Error\n");
			return 0;
		}
	}
	i = -1;
	while (++i < args_temp->num_philo)
	{
		args[i].num_philo = args_temp->num_philo;
		args[i].t_die = args_temp->t_die;
		args[i].t_eat = args_temp->t_eat;
		args[i].t_sleep = args_temp->t_sleep;
		args[i].num_t_philo = args_temp->num_t_philo;
		args[i].eating = 0;
		args[i].philo_id = i;
		args[i].time = 0;
		args[i].mutex = mutex;
		args[i].m_eat = eat;
		args[i].display = &display;
	}
	free(args_temp);
    creat_threads(&args);
	gettimeofday(&tv, NULL);
	while (1)
	{
		i = -1;
	
		while (++i < args->num_philo)
		{
			pthread_mutex_lock(&args[i].m_eat[i]);
			if ((get_time(args[i].start_simulation) - args[i].time) > (long)args[i].t_die)
			{
				if (args[i].eating == 0)
				{
					print_death(&args, get_time(tv), i);
					return (-1);
				}
			}
			pthread_mutex_unlock(&args[i].m_eat[i]);
		}
		usleep(300);
	}
    return (0);
}
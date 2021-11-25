/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-kass <ael-kass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 16:30:35 by ael-kass          #+#    #+#             */
/*   Updated: 2021/11/25 23:06:00 by ael-kass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

size_t		get_time(struct timeval	tv)
{
	struct timeval	tv1;
	size_t			time;
	
	gettimeofday(&tv1, NULL);
	time = ((tv1.tv_sec * 1000) + (tv1.tv_usec / 1000)) 
		- ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
	return (time);
}

void	*routine(void *args)
{
  	arguments_t		*args1;
	struct timeval	tv;
	//int				i;

	args1 = (arguments_t *)args;
	if (args1->philo_id % 2)
		usleep(400);
	gettimeofday(&tv, NULL);
	while (1)
	{
		// time when start ///
		// gettimeofday(&tv, NULL);
		// time = tv.tv_usec;
		//printf("philo %d, time = %ld\n",args1->philo_id, tv.tv_usec);
		// take the forks/////////
		pthread_mutex_lock(&args1->mutex[args1->philo_id]);
		printf("%zu %d has taken a fork\n", get_time(tv), args1->philo_id + 1);
		pthread_mutex_lock(&args1->mutex[(args1->philo_id + 1) % args1->num_philo]);
		printf("%zu %d has taken a fork\n", get_time(tv), args1->philo_id + 1);
		//////////start eating and unlock ////////////
		

		
		pthread_mutex_lock(&args1->m_eat[args1->philo_id]);
		

		
		args1->time = get_time(tv);
		printf("%zu %d is eating\n", get_time(tv), args1->philo_id + 1);
		usleep(args1->t_eat * 1000);
		pthread_mutex_unlock(&args1->mutex[args1->philo_id]);
		pthread_mutex_unlock(&args1->mutex[(args1->philo_id + 1) % args1->num_philo]);



		
		pthread_mutex_unlock(&args1->m_eat[args1->philo_id]);


		
		// start sleeping /////////
		printf("%zu %d is sleeping\n", get_time(tv), args1->philo_id + 1);
		usleep(args1->t_sleep * 1000);
		// start thinking ////////////
		printf("%zu %d is thinking\n", get_time(tv), args1->philo_id + 1);
		/// start when end /////
		//printf("philo %d, last_time = %d\n",args1->philo_id + 1, (tv.tv_usec - time) / 1000);
	}
}

void	creat_threads(arguments_t **args)
{
	pthread_t			*th;
	int					i;

	th = (pthread_t *)malloc((*args)->num_philo * sizeof(pthread_t));
	i = -1;
	while (++i < (*args)->num_philo)
	{
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
			//perror("mutex");
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
	struct timeval		tv;
	int					i;
	pthread_mutex_t		*eat;

	args_temp = (arguments_t *)malloc(sizeof(arguments_t));
	parsing(argc - 1, argv, &args_temp);
	mutex = (pthread_mutex_t *)malloc(args_temp->num_philo * sizeof(pthread_mutex_t));
	eat = (pthread_mutex_t *)malloc(args_temp->num_philo * sizeof(pthread_mutex_t));
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
	printf("num_philo %d\n", args_temp->num_philo);
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
	}
	free(args_temp);
    creat_threads(&args);
	gettimeofday(&tv, NULL);
	while (1)
	{
		i = -1;
		
		while (++i < args->num_philo)
		{
			//printf(" RETURN :%d\n",pthread_mutex_lock(&args[i].m_eat[i]));
			// printf("%zu\n", get_time(tv) - args[i].time);
			if ((get_time(tv) - args[i].time) >= (size_t)args[i].t_die)
			{
				printf("%zu %d died\n", get_time(tv), args[i].num_philo);
				return (-1);
			}
			pthread_mutex_unlock(&args[i].m_eat[i]);
		}
		
		usleep(300);
	}
    return (0);
}
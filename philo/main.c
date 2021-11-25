/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-kass <ael-kass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 16:30:35 by ael-kass          #+#    #+#             */
/*   Updated: 2021/11/25 18:39:12 by ael-kass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*routine(void *args)
{
  	arguments_t		*args1;
	struct timeval	tv;
	int		time;

	args1 = (arguments_t *)args;
	while (1)
	{
		// time when start ///
		gettimeofday(&tv, NULL);
		time = tv.tv_usec;
		//printf("philo %d, time = %ld\n",args1->philo_id, tv.tv_usec);
		if (args1->philo_id % 2)
			usleep(400);
		// take the forks/////////
		pthread_mutex_lock(&args1->mutex[args1->philo_id]);
		printf("%d has taken a fork\n", args1->philo_id + 1);
		pthread_mutex_lock(&args1->mutex[(args1->philo_id + 1) % args1->num_philo]);
		printf("%d has taken a fork\n", args1->philo_id + 1);
		//start eating and unlock ////////////
		printf("%d is eating\n", args1->philo_id + 1);
		usleep(args1->t_eat * 1000);
		pthread_mutex_unlock(&args1->mutex[args1->philo_id]);
		pthread_mutex_unlock(&args1->mutex[(args1->philo_id + 1) % args1->num_philo]);
		// start sleeping /////////
		printf("%d is sleeping\n", args1->philo_id + 1);
		usleep(args1->t_sleep * 1000);
		// start thinking ////////////
		printf("%d is thinking\n", args1->philo_id + 1);
		/// start when end /////
		gettimeofday(&tv, NULL);
		time = (tv.tv_usec - time) / 1000;
		printf("TIME :%d\n", time);
		if (time > args1->t_die)
		{
			printf("%d died\n", args1->philo_id + 1);
			exit(EXIT_FAILURE);
		}
		//printf("philo %d, last_time = %d\n",args1->philo_id + 1, (tv.tv_usec - time) / 1000);
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

void	creat_threads(arguments_t *args)
{
	pthread_t			*th;
	int					i;

	th = (pthread_t *)malloc(args->num_philo * sizeof(pthread_t));
	i = -1;
	while (++i < args->num_philo)
	{
		if (pthread_create(th + i, NULL, &routine, &args[i]))
		{
			printf("Error\n");
			return ;
		}
	}
	i = -1;
	while (++i < args->num_philo)
	{
		if (pthread_mutex_destroy(&args->mutex[i]))
		{
			//perror("mutex");
			return ;
		}
	}
}

int	main(int argc, char *argv[])
{
   // pthread_t			t1;
	arguments_t			*args_temp;
	arguments_t			*args;
	pthread_mutex_t		*mutex;
	int					i;

	args_temp = (arguments_t *)malloc(sizeof(arguments_t));
	parsing(argc - 1, argv, &args_temp);
	mutex = (pthread_mutex_t *)malloc(args_temp->num_philo * sizeof(pthread_mutex_t));
	args = (arguments_t *)malloc(args_temp->num_philo * sizeof(arguments_t));
	i = -1;
	while (++i < args_temp->num_philo)
	{
		if (pthread_mutex_init(&mutex[i], NULL))
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
		args[i].mutex = mutex;
	}
	free(args_temp);
    creat_threads(args);
	while (1)
	{
	}
    return (0);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-kass <ael-kass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 16:30:35 by ael-kass          #+#    #+#             */
/*   Updated: 2021/11/28 19:46:46 by ael-kass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long	get_time(struct timeval	tv)
{
	struct timeval	tv1;
	long			time;

	gettimeofday(&tv1, NULL);
	time = ((tv1.tv_sec * 1000) + (tv1.tv_usec / 1000)) 
		- ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
	return (time);
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
		print_actions(args1, "has taken a fork");
		pthread_mutex_lock(&args1->mutex[(args1->philo_id + 1) % args1->num_philo]);
		print_actions(args1, "has taken a fork");
		eating(args1);
		is_sleeping(args1);
		print_actions(args1, "is thinking");
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
		pthread_mutex_destroy(&(*args)->mutex[i]);
	free(th);
}

int	main(int argc, char *argv[])
{
	arguments_t			*args_temp;
	arguments_t			*args;
	pthread_mutex_t		*mutex;
	struct timeval		tv;

	args_temp = (arguments_t *)malloc(sizeof(arguments_t));
	parsing(argc - 1, argv, &args_temp);
	args_temp->finish_eat = (int *)malloc(sizeof(int));
	*(args_temp->finish_eat) = 0;
	mutex = (pthread_mutex_t *)malloc(args_temp->num_philo * sizeof(pthread_mutex_t));
	args = init_struct(args_temp, mutex, -1);
	free(args_temp);
    creat_threads(&args);
	gettimeofday(&tv, NULL);
	controler(&args, tv);
	free(args->finish_eat);
    return (0);
}
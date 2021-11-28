/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-kass <ael-kass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/28 16:46:39 by ael-kass          #+#    #+#             */
/*   Updated: 2021/11/28 19:35:29 by ael-kass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	init_mutex(arguments_t *args, pthread_mutex_t **mutex, pthread_mutex_t **eat)
{
	int		i;

	i = -1;
	while (++i < args->num_philo)
	{
		if (pthread_mutex_init(&(*mutex)[i], NULL))
		{
			printf("Error\n");
			return (1);
		} 
		if (pthread_mutex_init(&(*eat)[i], NULL))
		{
			printf("Error\n");
			return (1);
		}
	}
	return (0);
}

arguments_t	*init_struct(arguments_t *args_temp, pthread_mutex_t *mutex, int i)
{
	arguments_t			*args;
	pthread_mutex_t		display;
	pthread_mutex_t		*eat;

	eat = (pthread_mutex_t *)malloc(args_temp->num_philo * sizeof(pthread_mutex_t));
	init_mutex(args_temp, &mutex, &eat);
	pthread_mutex_init(&display, NULL);
	args = (arguments_t *)malloc(args_temp->num_philo * sizeof(arguments_t));
	while (++i < args_temp->num_philo)
	{
		args[i].num_philo = args_temp->num_philo;
		args[i].t_die = args_temp->t_die;
		args[i].t_eat = args_temp->t_eat;
		args[i].t_sleep = args_temp->t_sleep;
		args[i].num_t_philo = args_temp->num_t_philo;
		args[i].eating = 0;
		args[i].num_eat = 0;
		args[i].finish_eat = args_temp->finish_eat;
		args[i].philo_id = i;
		args[i].time = 0;
		args[i].mutex = mutex;
		args[i].m_eat = eat;
		args[i].display = &display;
	}
	return (args);
}
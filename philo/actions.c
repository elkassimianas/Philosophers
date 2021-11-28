/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-kass <ael-kass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/28 11:36:37 by ael-kass          #+#    #+#             */
/*   Updated: 2021/11/28 19:31:55 by ael-kass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void    eating(arguments_t *args)
{
	args->eating = 1;
	pthread_mutex_lock(&args->m_eat[args->philo_id]);
	args->num_eat += 1;
	if (args->num_eat == args->num_t_philo)
		*(args->finish_eat) += 1;
	args->time = get_time(args->start_simulation);
	print_actions(args, "is eating");
	usleep_(args->t_eat * 1000);
	pthread_mutex_unlock(&args->mutex[args->philo_id]);
	pthread_mutex_unlock(&args->mutex[(args->philo_id + 1) % args->num_philo]);
	pthread_mutex_unlock(&args->m_eat[args->philo_id]);
	args->eating = 0;
}

void	is_sleeping(arguments_t *args)
{
	print_actions(args, "is sleeping");
	usleep_(args->t_sleep * 1000);
}
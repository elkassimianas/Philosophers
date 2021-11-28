/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-kass <ael-kass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 21:58:39 by ael-kass          #+#    #+#             */
/*   Updated: 2021/11/28 19:36:25 by ael-kass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>

typedef	struct	arguments_s
{
	int		num_philo;
	int		t_die;
	int		t_eat;
	int		t_sleep;
	int		num_t_philo;
	int		eating;
	int		philo_id;
	int		num_eat;
	int		*finish_eat;
	long	time;
	struct timeval	start_simulation;
	pthread_mutex_t *mutex;
	pthread_mutex_t *m_eat;
	pthread_mutex_t *display;
}				arguments_t;

void	ft_putstr(char *s);
int		ft_isdigit(int c);
void	print_error();
int		ft_atoi(const char *str);
void    eating(arguments_t *args);
void	is_sleeping(arguments_t *args);
void    controler(arguments_t **args, struct timeval tv);
void	print_death(arguments_t *args, long time, int i);
long	get_time(struct timeval	tv);
void	usleep_(useconds_t usec);
void	print_actions(arguments_t *args, char *str);
void	creat_threads(arguments_t **args);
void	parsing(int len, char **argv, arguments_t **args);
int	init_mutex(arguments_t *args, pthread_mutex_t **mutex, pthread_mutex_t **eat);
arguments_t	*init_struct(arguments_t *args_temp, pthread_mutex_t *mutex, int i);
void	print_death(arguments_t *args, long time, int i);
void	print_actions(arguments_t *args, char *str);

#endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-kass <ael-kass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 21:58:39 by ael-kass          #+#    #+#             */
/*   Updated: 2021/11/25 15:26:34 by ael-kass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>

typedef struct s_mutex
{
	pthread_mutex_t *fork;
	pthread_mutex_t m_eat;
}				t_mutex;

typedef	struct	arguments_s
{
	int	num_philo;
	int	t_die;
	int	t_eat;
	int	t_sleep;
	int	num_t_philo;
	int	eating;
	int	philo_id;
	pthread_mutex_t *mutex;
}				arguments_t;	

void	ft_putstr(char *s);
int	ft_isdigit(int c);
void	print_error();
int	ft_atoi(const char *str);

#endif
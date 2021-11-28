/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-kass <ael-kass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/28 16:10:19 by ael-kass          #+#    #+#             */
/*   Updated: 2021/11/28 17:38:48 by ael-kass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

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
	else
		(*args)->num_t_philo = -1;
}
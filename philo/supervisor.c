/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   supervisor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-kass <ael-kass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/28 11:47:57 by ael-kass          #+#    #+#             */
/*   Updated: 2021/11/28 19:39:39 by ael-kass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

// int	check_eat(arguments_t **args)
// {
// 	int		i;

// 	i = -1;
// 	printf("NUM PHILO %d\n", (*args)[0].num_philo);
// 	while (++i < (*args)[0].num_philo)
// 	{
// 		printf("ID %d TIME EAT %d\n", i, (*args)[i].num_eat);
// 		if ((*args)[i].num_eat < (*args)[i].num_t_philo)
// 			return (0);
// 	}
// 	return(1);
// }

void    controler(arguments_t **args, struct timeval tv)
{
    int     i;

    while (1)
	{
		i = -1;
		while (++i < (*args)[0].num_philo)
		{
			pthread_mutex_lock(&((*args)[i].m_eat[i]));
			if ((get_time((*args)[i].start_simulation) - (*args)[i].time) > (long)((*args)[i].t_die))
			{
				if ((*args)[i].eating == 0)
				{
					print_death(*args, get_time(tv), i);
					return ;
				}
			}
		//	printf("FINISH TO EAT %d\n", (*(*args)[0].finish_eat));
			if ((*args)[i].num_t_philo != -1 && (*(*args)[i].finish_eat == (*args)[i].num_philo))
				return ;
			pthread_mutex_unlock(&(*args)[i].m_eat[i]);
		}
		usleep(600);
	}
}
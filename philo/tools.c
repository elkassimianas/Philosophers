/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-kass <ael-kass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 21:57:11 by ael-kass          #+#    #+#             */
/*   Updated: 2021/11/28 16:50:11 by ael-kass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "philosophers.h"

void	ft_putstr(char *s)
{
	int		i;

	i = 0;
	if (s == NULL)
		return ;
	while (s[i] != '\0')
	{
		write(2, &s[i], 1);
		i++;
	}
}
void	print_error()
{
    ft_putstr("Error\n");
    exit(EXIT_FAILURE);
}

int	ft_isdigit(int c)
{
	if (48 <= c && c <= 57)
		return (1);
	else
		return (0);
}

void	print_death(arguments_t *args, long time, int i)
{
	pthread_mutex_lock(args[i].display);
	printf("%ld %d died\n", time, args[i].philo_id);
}

void	print_actions(arguments_t *args, char *str)
{
		pthread_mutex_lock(args->display);
		printf("%ld %d %s\n", get_time(args->start_simulation), args->philo_id + 1, str);
		pthread_mutex_unlock(args->display);
}

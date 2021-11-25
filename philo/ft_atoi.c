/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-kass <ael-kass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 13:03:29 by ael-kass          #+#    #+#             */
/*   Updated: 2021/11/25 14:14:13 by ael-kass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	is_space(char c)
{
	return ((c >= 9 && c <= 13) || c == 32);
}

static int	ft_passing(const char *str)
{
	int		i;

	i = 0;
	while (is_space(str[i]))
		i++;
	return (i);
}

static int	ft_atoi_help(const char *str, long nb, int sign, int i)
{
	while (str[i])
	{
		if (nb < 0 || str[i] < 48 || str[i] > 57)
			print_error();
		nb = nb * 10 + (str[i] - 48);
		i++;
	}
	if (nb > 2147483647 || nb < -2147483648)
	{
		ft_putstr("Error\n");
		exit(EXIT_FAILURE);
	}
	nb = nb * sign;
	return (nb);
}

int	ft_atoi(const char *str)
{
	long		nb;
	int			sign;
	int			i;

	i = 0;
	nb = 0;
	sign = 1;
	i = ft_passing(str);
	if (str[i] == '+')
		i++;
	else if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	return (ft_atoi_help (str, nb, sign, i));
}
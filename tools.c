/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-kass <ael-kass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 21:57:11 by ael-kass          #+#    #+#             */
/*   Updated: 2021/11/19 16:53:05 by ael-kass         ###   ########.fr       */
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
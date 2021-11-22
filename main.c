/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-kass <ael-kass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 16:30:35 by ael-kass          #+#    #+#             */
/*   Updated: 2021/11/19 18:49:38 by ael-kass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*routine()
{
    printf("Test from threads\n");
    return (NULL);
}

void	parsing(int len, char **argv, arguments_t *args)
{
	if (len > 5 || len < 4)
		print_error();
	args->num_philo = ft_atoi(argv[1]);
	if (args->num_philo <= 0)
        print_error();
	args->t_die = ft_atoi(argv[2]);
	args->t_eat = ft_atoi(argv[3]);
	args->t_sleep = ft_atoi(argv[4]);
	if (args->t_die < 0 || args->t_eat < 0 || args->t_sleep < 0)
		print_error();
	if (len == 5)
	{
		args->num_t_philo = ft_atoi(argv[5]);
		if (args->num_t_philo < 0)
			print_error();
	}
}

int	main(int argc, char *argv[])
{
    pthread_t		t1;
	arguments_t		args;

	parsing(argc - 1, argv, &args);
    if(pthread_create(&t1, NULL, &routine, NULL))
		return (1);
    if (pthread_join(t1, NULL))
		return (1);
    return (0);
}
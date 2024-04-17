/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilbendib <ilbendib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 13:15:41 by ilbendib          #+#    #+#             */
/*   Updated: 2024/03/29 11:50:08 by ilbendib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	ft_error_msg(char *msg)
{
	printf("Error: %s\n", msg);
	return ;
}

int	main(int ac, char **av)
{
	t_philo			philo[PHILO_MAX];
	t_table			table;
	pthread_mutex_t	forks[PHILO_MAX];

	if (!check_args(av))
		return (1);
	if (ac == 5 || ac == 6)
	{
		ft_init_param(&table, philo);
		ft_init_forks(forks, ft_atoi((av[1]), NULL));
		ft_init_philos(philo, &table, forks, av);
		ft_creat_thread_philo(&table, forks);
		destroy_mutex_init(NULL, &table, forks);
	}
	else
	{
		printf("wrong number of arguments\n");
		return (1);
	}
	return (0);
}

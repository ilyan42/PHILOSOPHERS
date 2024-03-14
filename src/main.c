/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilbendib <ilbendib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 13:15:41 by ilbendib          #+#    #+#             */
/*   Updated: 2024/03/14 12:00:37 by ilbendib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	ft_error_msg(char *msg)
{
	printf("Error: %s\n", msg);
	exit(EXIT_FAILURE);
}

int	ft_check_args(int ac, char **av)
{
	if (ft_atoi(av[1]) < 1 || ft_atoi(av[1]) > PHILO_MAX)
	{
		return (ft_error_msg("wrong number of philosophers"),
			0);
	}
	if (ft_atoi(av[2]) < 1 || ft_atoi(av[2]) > INT_MAX)
		return (ft_error_msg("wrong number of time to died"), 0);
	if (ft_atoi(av[3]) < 1 || ft_atoi(av[3]) > INT_MAX)
		return (ft_error_msg("wrong number of time to eat"), 0);
	if (ft_atoi(av[4]) < 1 || ft_atoi(av[4]) > INT_MAX)
		return (ft_error_msg("wrong number of time to sleep"), 0);
	if (ac == 6)
	{
		if (ft_atoi(av[5]) < 1 || ft_atoi(av[5]) > INT_MAX)
		{
			return (ft_error_msg("wrong number of number to eat"), 0);
		}
	}
}

int	main(int ac, char **av)
{
	t_philo			philo[PHILO_MAX];
	t_table		table;
	pthread_mutex_t	forks[PHILO_MAX];

	if (ac < 5 || ac > 6)
		ft_error_msg("Wrong number of arguments");
	if (ft_check_args(ac, av) == 0)
		return (1);
	ft_init_param(&table, philo);
	ft_init_forks(forks, ft_atoi(av[1]));
	ft_init_philos(philo, &table, forks, av);
	ft_creat_thread_philo(&table, forks);
	destroy_mutex_init(NULL, &table, forks);
	return (0);
}

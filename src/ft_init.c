/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilbendib <ilbendib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 16:22:48 by ilyanbendib       #+#    #+#             */
/*   Updated: 2024/02/12 18:46:48 by ilbendib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int ft_init_param(t_philo *philo, char **av)
{
	philo->num_of_philos = atoi(av[1]);
	philo->time_to_die = atoi(av[2]);
	philo->time_to_eat = atoi(av[3]);
	philo->time_to_sleep = atoi(av[4]);
	philo->num_times_to_eat = -1;
	philo->dead = 0;
	if (philo->num_of_philos <= 0 || philo->time_to_die <= 0 || philo->time_to_eat <= 0 || philo->time_to_sleep <= 0)
	{
		printf("Error: wrong arguments\n");
		return (0);
	}
	if (av[5])
	{
		philo->num_times_to_eat = atoi(av[5]);
		if (philo->num_times_to_eat <= 0)
		{
			printf("Error: wrong number of times to eat\n");
			return (0);
		}
	}
	return (1);
}

int creat_philo(t_philo *philo)
{
	int i;

	i = 0;
	philo[i].num_of_fork_in_table = 0;
	while (i < philo->num_of_philos)
	{
		pthread_create(&philo[i].thread, NULL, &routine, &philo[i]);
		pthread_join(philo[i].thread, NULL);
		philo[i].num_of_fork_in_table++;
		i++;
	}
	return (1);
}

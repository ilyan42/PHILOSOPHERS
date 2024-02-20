/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilbendib <ilbendib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 16:22:48 by ilyanbendib       #+#    #+#             */
/*   Updated: 2024/02/16 12:47:24 by ilbendib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void ft_init_args(t_philo *philo, char **av)
{
	philo->num_of_philos = atoi(av[1]);
	philo->time_to_die = atoi(av[2]);
	philo->time_to_eat = atoi(av[3]);
	philo->time_to_sleep = atoi(av[4]);
	philo->num_times_to_eat = -1;
}

int creat_philo(t_philo *philo)
{
	int i;

	i = 0;
	while (i < philo->num_of_philos)
	{
		pthread_create(&philo[i].thread, NULL, &routine, &philo[i]);
		pthread_join(philo[i].thread, NULL);
		i++;
	}
	return (1);
}

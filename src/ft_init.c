/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilyanbendib <ilyanbendib@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 16:22:48 by ilyanbendib       #+#    #+#             */
/*   Updated: 2024/02/09 19:31:08 by ilyanbendib      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int ft_init_param(t_philo *philo, char **av)
{
	if (atoi(av[1]) < 2)
	{
		printf("Error: wrong number of philosophers\n");
		exit(1);
	}
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

int creat_philo(t_philo *philos)
{
	int i;

	i = 0;
	philos = malloc(sizeof(t_philo) * philos->num_of_philos);
	if (!philos)
		return (0);
	while (i < philos->num_of_philos)
	{
		pthread_create(&philos[i].philo, NULL, &routine, NULL);
		i++;
	}
	return (1);
}

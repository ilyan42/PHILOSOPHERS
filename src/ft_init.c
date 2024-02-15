/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilyanbendib <ilyanbendib@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 16:22:48 by ilyanbendib       #+#    #+#             */
/*   Updated: 2024/02/15 12:29:12 by ilyanbendib      ###   ########.fr       */
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
    philo->meals_eaten = 0;
    philo->last_meal = 0;
    philo->start_time = get_current_time();
    init_mutex(philo);
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

void init_mutex(t_philo *philo)
{
    int i;

    i = 0;
    while (i < philo->num_of_philos)
    {
        pthread_mutex_init(&philo[i].r_fork, NULL);
        pthread_mutex_init(&philo[i].l_fork, NULL);
        pthread_mutex_init(&philo[i].think_lock, NULL);
        pthread_mutex_init(&philo[i].dead_lock, NULL);
        pthread_mutex_init(&philo[i].meal_lock, NULL);
        i++;
    }
}

void init_one_philo(t_philo *philo, int id, t_program *program)
{
	philo->l_fork = id;
	philo->r_fork = (id + 1) % program->philos->num_of_philos;
	philo->eating = 0;
	philo->meals_eaten = 0;
	philo->last_meal = 0;
}

void init_all_philo(t_program *program)
{
    int i;

    i = 0;
    program->philos = malloc(sizeof(t_philo) * program->philos->num_of_philos);
    if (!program->philos)
        ft_error_msg("malloc failed");
    while (i < program->philos->num_of_philos)
    {
		init_one_philo(&program->philos[i], i, program);
    }
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilbendib <ilbendib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 16:22:48 by ilyanbendib       #+#    #+#             */
/*   Updated: 2024/03/25 12:02:08 by ilbendib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	ft_init_args(t_philo *philo, char **av)
{
	philo->num_of_philos = ft_atoi((av[1]), NULL);
	philo->tt_d = ft_atoi((av[2]), NULL);
	philo->tt_e = ft_atoi((av[3]), NULL);
	philo->tt_s = ft_atoi((av[4]), NULL);
	if (av[5])
		philo->num_times_to_eat = ft_atoi((av[5]), NULL);
	else
		philo->num_times_to_eat = -1;
}

void	ft_init_philos(t_philo *philos, t_table *table,
		pthread_mutex_t *forks, char **argv)
{
	int	i;

	i = 0;
	while (i < ft_atoi((argv[1]), NULL))
	{
		philos[i].id = i + 1;
		philos[i].eating = 0;
		philos[i].meals_eaten = 0;
		ft_init_args(&philos[i], argv);
		philos[i].start_time = timestamp();
		philos[i].last_meal = timestamp();
		philos[i].print_lock = &table->print_lock;
		philos[i].dead_lock = &table->dead_lock;
		philos[i].meal_lock = &table->meal_lock;
		philos[i].dead = &table->dead_flag;
		philos[i].l_fork = &forks[i];
		philos[i].r_fork = &forks[(i + 1) % philos[0].num_of_philos];
		i++;
	}
}

int	ft_creat_thread_philo(t_table *table, pthread_mutex_t *forks)
{
	pthread_t	philos;
	int			i;

	if (pthread_create(&philos, NULL, &loop_dead, table->philos) != 0)
		destroy_mutex_init("Thread creation fail", table, forks);
	i = 0;
	while (i < table->philos[0].num_of_philos)
	{
		if (pthread_create(&table->philos[i].thread, NULL, &routine,
				&table->philos[i]) != 0)
			destroy_mutex_init("Thread creation fail", table, forks);
		i++;
	}
	if (pthread_join(philos, NULL) != 0)
		destroy_mutex_init("Thread join fail", table, forks);
	i = 0;
	while (i < table->philos[0].num_of_philos)
	{
		if (pthread_join(table->philos[i].thread, NULL) != 0)
			destroy_mutex_init("Thread join fail", table, forks);
		i++;
	}
	return (0);
}

void	ft_init_param(t_table *table, t_philo *philo)
{
	table->dead_flag = 0;
	table->philos = philo;
	pthread_mutex_init(&table->dead_lock, NULL);
	pthread_mutex_init(&table->meal_lock, NULL);
	pthread_mutex_init(&table->print_lock, NULL);
}

void	ft_init_forks(pthread_mutex_t *forks, int num_of_philos)
{
	int	i;

	i = 0;
	while (i < num_of_philos)
	{
		pthread_mutex_init(&forks[i], NULL);
		i++;
	}
}

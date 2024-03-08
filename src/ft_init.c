/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilbendib <ilbendib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 16:22:48 by ilyanbendib       #+#    #+#             */
/*   Updated: 2024/03/08 17:33:32 by ilbendib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void ft_init_args(t_philo *philo, char **av)
{
	philo->num_of_philos = ft_atoi(av[1]);
	philo->time_to_die = ft_atoi(av[2]);
	philo->time_to_eat = ft_atoi(av[3]);
	philo->time_to_sleep = ft_atoi(av[4]);
	if (av[5])
		philo->num_times_to_eat = ft_atoi(av[5]);
	else
		philo->num_times_to_eat = -1;
}

void	ft_init_philos(t_philo *philos, t_program *program, pthread_mutex_t *forks,
		char **argv)
{
	int	i;

	i = 0;
	while (i < ft_atoi(argv[1]))
	{
		philos[i].id = i + 1;
		philos[i].eating = 0;
		philos[i].meals_eaten = 0;
		ft_init_args(&philos[i], argv);
		philos[i].start_time = get_current_time();
		philos[i].last_meal = get_current_time();
		philos[i].print_lock = &program->print_lock;
		philos[i].dead_lock = &program->dead_lock;
		philos[i].meal_lock = &program->meal_lock;
		philos[i].dead = &program->dead_flag;
		philos[i].l_fork = &forks[i];
		philos[i].r_fork = &forks[(i + 1) % philos[0].num_of_philos];
		i++;
	}
}

int	ft_creat_thread_philo(t_program *program, pthread_mutex_t *forks)
{
	pthread_t	philos;
	int			i;

	if (pthread_create(&philos, NULL, &loop_dead, program->philos) != 0)
		destroy_mutex_init("Thread creation error", program, forks);
	i = 0;
	while (i < program->philos[0].num_of_philos)
	{
		if (pthread_create(&program->philos[i].thread, NULL, &routine,
				&program->philos[i]) != 0)
			destroy_mutex_init("Thread creation error", program, forks);
		i++;
	}
	i = 0;
	// if (pthread_join(phlios, NULL) != 0)
	// 	destroy_mutex_init("Thread join error", program, forks);
	while (i < program->philos[0].num_of_philos)
	{
		if (pthread_join(program->philos[i].thread, NULL) != 0)
			destroy_mutex_init("Thread join error", program, forks);
		i++;
	}
	return (0);
}

void ft_init_param(t_program *program, t_philo *philo)
{
	program->dead_flag = 0;
	program->philos = philo;
	pthread_mutex_init(&program->dead_lock, NULL);
	pthread_mutex_init(&program->meal_lock, NULL);
	pthread_mutex_init(&program->print_lock, NULL);
}

void ft_init_forks(pthread_mutex_t *forks, int num_of_philos)
{
	int i;

	i = 0;
	while (i < num_of_philos)
	{
		pthread_mutex_init(&forks[i], NULL);
		i++;
	}
}
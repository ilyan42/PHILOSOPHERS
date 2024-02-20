/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilbendib <ilbendib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 13:15:41 by ilbendib          #+#    #+#             */
/*   Updated: 2024/02/16 14:21:33 by ilbendib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void ft_error_msg(char *msg)
{
    printf("Error: %s\n", msg);
    exit(EXIT_FAILURE);
}

void ft_init_param(t_program *program, t_philo *philo)
{
	program->philos = philo;
	program->dead_flag = 0;
	pthread_mutex_init(&program->dead_lock, NULL);
	pthread_mutex_init(&program->meal_lock, NULL);
	pthread_mutex_init(&program->think_lock, NULL);
}

void ft_init_forks(pthread_mutex_t *forks, char **av)
{
	int i;

	i = 0;
	while (i < ft_atoi(av[1]))
	{
		pthread_mutex_init(&forks[i], NULL);
		i++;
	}
}

int ft_check_args(t_philo *philo, char **av)
{
	// if (philo->num_of_philos <= 0 || philo->time_to_die <= 0 || philo->time_to_eat <= 0 || philo->time_to_sleep <= 0)
	// {
	// 	printf("Error: wrong arguments\n");
	// 	return (0);
	// }
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

void ft_init_philos(t_philo *philo, t_program *program, pthread_mutex_t *forks, char **av)
{
	int i;

	i = 0;
	while (i < philo->num_of_philos)
	{
		philo[i].id = i;
		philo[i].eating = 0;
		philo[i].meals_eaten = 0;
		philo[i].last_meal = get_current_time();
		philo[i].start_time = get_current_time();
		philo[i].dead = 0;
		philo[i].think_lock = &program->think_lock;
		philo[i].dead_lock = &program->dead_lock;
		philo[i].meal_lock = &program->meal_lock;
		philo[i].l_fork = &forks[i];
		philo[i].r_fork = &forks[(i + 1) % philo->num_of_philos];
		i++;
	}
}

int main(int ac, char **av)
{
	t_philo philo[PHILO_MAX];
	t_program program;
	pthread_mutex_t forks[PHILO_MAX];

	if (ft_check_args(philo, av) == 0)
		return(0);
	ft_init_param(&program, philo);
	ft_init_forks(forks, av);
	ft_init_args(philo, av);
	printf("num_of_philos: %d\n", philo->num_of_philos);
	printf("time_to_die: %zu\n", philo->time_to_die);
	printf("time_to_eat: %zu\n", philo->time_to_eat);
	printf("time_to_sleep: %zu\n", philo->time_to_sleep);
	printf("num_times_to_eat: %d\n", philo->num_times_to_eat);
	printf("forks: %d\n", ft_atoi(av[1]));
	ft_init_philos(philo, &program, forks, av);
	creat_philo(philo);
	return 0;
}



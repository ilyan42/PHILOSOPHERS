/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilbendib <ilbendib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 13:15:41 by ilbendib          #+#    #+#             */
/*   Updated: 2024/03/08 17:30:06 by ilbendib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void ft_error_msg(char *msg)
{
    printf("Error: %s\n", msg);
    exit(EXIT_FAILURE);
}

int ft_check_args(t_philo *philo, char **av)
{
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

int main(int ac, char **av)
{
	t_philo philo[PHILO_MAX];
	t_program program;
	pthread_mutex_t forks[PHILO_MAX];

	// if (ft_check_args(philo, av) == 0)
	// 	return(0);
	ft_init_param(&program, philo);
	ft_init_forks(forks, ft_atoi(av[1]));
	ft_init_philos(philo, &program, forks, av);	
	ft_creat_thread_philo(&program, forks);
	destroy_mutex_init(NULL, &program, forks);
	return 0;
}



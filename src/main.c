/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilyanbendib <ilyanbendib@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 13:15:41 by ilbendib          #+#    #+#             */
/*   Updated: 2024/02/09 19:14:17 by ilyanbendib      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int main(int ac, char **av)
{
	t_philo *philo;

	philo = malloc(sizeof(t_philo));
	if (ac != 6)
	{
		printf("Error: wrong number of arguments\n");
		return (1);
	}
	if (ft_init_param(philo, av) == 0)
		return (EXIT_FAILURE);
	printf ("philo->num_of_philos = %d\n", philo->num_of_philos);
	printf ("philo->time_to_die = %zu\n", philo->time_to_die);
	printf ("philo->time_to_eat = %zu\n", philo->time_to_eat);
	printf ("philo->time_to_sleep = %zu\n", philo->time_to_sleep);
	printf ("philo->num_times_to_eat = %d\n", philo->num_times_to_eat);
	return 0;
}


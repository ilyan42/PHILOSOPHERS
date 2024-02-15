/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_routine_philo.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilyanbendib <ilyanbendib@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 19:31:32 by ilyanbendib       #+#    #+#             */
/*   Updated: 2024/02/15 12:29:23 by ilyanbendib      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

size_t	get_current_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		write(2, "gettimeofday() error\n", 22);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

int	ft_usleep(size_t milliseconds)
{
	size_t	start;

	start = get_current_time();
	while ((get_current_time() - start) < milliseconds)
		usleep(50);
	printf("sleeping\n");
	return (0);
}

int sleeping(t_philo *philo)
{
	ft_usleep(philo->time_to_sleep);
	return (0);
}

void eat(t_philo *philo)
{
	printf("eat");
	take_fork(philo);
}

void think(t_philo *philo)
{
	printf("think");
	pthread_mutex_lock(philo->think_lock);
	// ft_usleep(philo->tim)
	pthread_mutex_unlock(philo->think_lock);
}

void *routine(void *arg)
{
	t_philo *philo = (t_philo *)arg;
	
	while (philo->dead == 0)
	{
		//eat(philo);
		sleeping(philo);
		// think(philo);
		// if (philo->num_times_to_eat != -1)
		// {
		// 	pthread_mutex_lock(philo->meal_lock);
		// 	philo->meals_eaten++;
		// 	if (philo->meals_eaten == philo->num_times_to_eat)
		// 		philo->dead = 1;
		// 	pthread_mutex_unlock(philo->meal_lock);
		// }
	}
	return (NULL);
}

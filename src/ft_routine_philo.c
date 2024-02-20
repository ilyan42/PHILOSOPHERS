/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_routine_philo.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilbendib <ilbendib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 19:31:32 by ilyanbendib       #+#    #+#             */
/*   Updated: 2024/02/20 13:40:23 by ilbendib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void print_philo(char *msg, t_philo *philo, int id)
{
	pthread_mutex_lock(philo->print_lock);
	printf("%ld %d %s\n", get_current_time() - philo->start_time, id, msg);
	pthread_mutex_unlock(philo->print_lock);
}
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
	return (0);
}

int sleeping(t_philo *philo)
{
	print_philo("is sleeping", philo, philo->id);
	ft_usleep(philo->time_to_sleep);
	return (0);
}

int ft_check_death(t_philo *philo)
{
	if (get_current_time() - philo->last_meal >= philo->time_to_die)
	{
		printf("is dead\n");
		return (philo->dead = 1);
	}
	return (1);
}

int take_a_fork(t_philo *philo)
{
	pthread_mutex_lock(philo->r_fork);
	print_philo("has taken r_fork", philo, philo->id);
	if (ft_check_death(philo) == 0)
		return (0);
	pthread_mutex_lock(philo->l_fork);
	print_philo("has taken l_fork", philo, philo->id);
	philo->eating = 1;
	print_philo("is eating", philo, philo->id);
	pthread_mutex_lock(philo->meal_lock);
	philo->last_meal = get_current_time();
	philo->meals_eaten++;
	pthread_mutex_unlock(philo->meal_lock);	
	ft_usleep(philo->time_to_eat);
	philo->eating = 0;
	pthread_mutex_unlock(philo->r_fork);
	pthread_mutex_unlock(philo->l_fork);
	if (ft_check_death(philo) == 0)
		return (0);
	return (1);
}

void think(t_philo *philo)
{
	print_philo("is thinking", philo, philo->id);
	while (!take_a_fork(philo))
	{
		ft_usleep(50);
		if (philo->dead == 1)
			exit(0);
	}
}


void *routine(void *arg)
{
	t_philo *philo = (t_philo *)arg;
	
	if (philo->id % 2 == 0)
		ft_usleep(100);
	while (philo->dead == 0)
	{
		take_a_fork(philo);
		if (philo->dead == 1)
			exit(0);
		sleeping(philo);
		if (ft_check_death(philo) == 0)
			exit(0);
		if (philo->dead == 1)
			exit(0);
		think(philo);
	}
	return (NULL);
}

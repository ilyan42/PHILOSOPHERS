/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_routine_philo.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilbendib <ilbendib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 19:31:32 by ilyanbendib       #+#    #+#             */
/*   Updated: 2024/02/22 11:49:18 by ilbendib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int check_died_flg(t_philo *philo)
{
	pthread_mutex_lock(philo->dead_lock);
	if (philo->dead == 1)
		return (pthread_mutex_unlock(philo->dead_lock), 1);
	return (pthread_mutex_unlock(philo->dead_lock), 0);
}

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

int	philosopher_dead(t_philo *philo, size_t time_to_die)
{
	pthread_mutex_lock(philo->meal_lock);
	if (get_current_time() - philo->last_meal >= time_to_die
		&& philo->eating == 0)
		return (pthread_mutex_unlock(philo->meal_lock), 1);
	pthread_mutex_unlock(philo->meal_lock);
	return (0);
}


void take_a_fork(t_philo *philo)
{
	pthread_mutex_lock(philo->r_fork);
	print_philo("has taken a fork", philo, philo->id);
	if (philo->num_of_philos == 1)
	{
		ft_usleep(philo->time_to_die);
		pthread_mutex_unlock(philo->r_fork);
		return ;
	}
	pthread_mutex_lock(philo->l_fork);
	print_philo("has taken a fork", philo, philo->id);
	philo->eating = 1;
	print_philo("is eating", philo, philo->id);
	pthread_mutex_lock(philo->meal_lock);
	philo->last_meal = get_current_time();
	philo->meals_eaten++;
	pthread_mutex_unlock(philo->meal_lock);
	ft_usleep(philo->time_to_eat);
	philo->eating = 0;
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
}

void think(t_philo *philo)
{
	print_philo("is thinking", philo, philo->id);
	ft_usleep(50);
}


void *routine(void *arg)
{
	t_philo *philo = (t_philo *)arg;
	
	if (philo->id % 2 == 0)
		ft_usleep(100);
	while (!check_died_flg(philo))
	{
		take_a_fork(philo);
		sleeping(philo);
		think(philo);
	}
	return (NULL);
}

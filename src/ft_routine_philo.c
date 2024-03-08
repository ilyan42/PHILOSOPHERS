/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_routine_philo.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilbendib <ilbendib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 19:31:32 by ilyanbendib       #+#    #+#             */
/*   Updated: 2024/03/08 17:15:51 by ilbendib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int sleeping(t_philo *philo)
{
	print_philo("is sleeping", philo, philo->id);
	ft_usleep(philo->time_to_sleep);
	return (0);
}

void think(t_philo *philo)
{
	print_philo("is thinking", philo, philo->id);
	// ft_usleep(philo->time_to_sleep);
}

void ft_just_only_one_philo(t_philo *philo)
{
	pthread_mutex_lock(philo->r_fork);
	print_philo("has taken a fork", philo, philo->id);
	ft_usleep(philo->time_to_die);
	return ;
}

void take_a_fork(t_philo *philo)
{
	if (philo->num_of_philos == 1)
	{
		ft_just_only_one_philo(philo);
		return ;
	}
	pthread_mutex_lock(philo->r_fork);
	print_philo("has taken a fork", philo, philo->id);
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

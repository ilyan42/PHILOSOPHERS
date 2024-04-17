/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_routine_philo.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilbendib <ilbendib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 19:31:32 by ilyanbendib       #+#    #+#             */
/*   Updated: 2024/03/29 12:24:51 by ilbendib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	thinking(t_philo *philo)
{
	print_philo("is thinking", philo, philo->id);
}

void	ft_just_only_one_philo(t_philo *philo)
{
	pthread_mutex_lock(philo->r_fork);
	print_philo("has taken a fork", philo, philo->id);
	ft_usleep(philo->tt_d);
	pthread_mutex_unlock(philo->r_fork);
	return ;
}

void	grab_forks_and_eat(t_philo *philo, pthread_mutex_t *first_fork,
		pthread_mutex_t *second_fork)
{
	pthread_mutex_lock(first_fork);
	print_philo("has taken a fork", philo, philo->id);
	pthread_mutex_lock(second_fork);
	print_philo("has taken a fork", philo, philo->id);
	philo->eating = 1;
	print_philo("is eating", philo, philo->id);
	pthread_mutex_lock(philo->meal_lock);
	philo->last_meal = timestamp();
	philo->meals_eaten++;
	pthread_mutex_unlock(philo->meal_lock);
	ft_usleep(philo->tt_e);
	philo->eating = 0;
	pthread_mutex_unlock(first_fork);
	pthread_mutex_unlock(second_fork);
}

void	take_a_fork(t_philo *philo)
{
	pthread_mutex_t	*first_fork;
	pthread_mutex_t	*second_fork;

	if (philo->r_fork < philo->l_fork)
	{
		first_fork = philo->r_fork;
		second_fork = philo->l_fork;
	}
	else
	{
		first_fork = philo->l_fork;
		second_fork = philo->r_fork;
	}
	grab_forks_and_eat(philo, first_fork, second_fork);
	ft_usleep(1);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		ft_usleep(0.9 * philo->tt_e);
	if (philo->num_of_philos == 1)
		ft_just_only_one_philo(philo);
	while (!check_died_flg(philo))
	{
		take_a_fork(philo);
		sleeping(philo);
		thinking(philo);
	}
	return (NULL);
}

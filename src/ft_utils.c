/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilbendib <ilbendib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 13:38:40 by ilbendib          #+#    #+#             */
/*   Updated: 2024/03/26 11:27:11 by ilbendib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	print_philo(char *msg, t_philo *philo, int id)
{
	size_t	time;

	time = timestamp() - philo->start_time;
	if (!check_died_flg(philo))
	{
		pthread_mutex_lock(philo->print_lock);
		printf("%06llu %d %s\n", timestamp()
			- philo->start_time, id, msg);
		pthread_mutex_unlock(philo->print_lock);
	}
}

long long	timestamp(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return (t.tv_sec * 1000 + t.tv_usec / 1000);
}

int	ft_usleep(size_t milliseconds)
{
	size_t	start;

	start = timestamp();
	while ((timestamp() - start) < milliseconds)
		usleep(500);
	return (0);
}

void	destroy_mutex_init(char *str, t_table *table,
		pthread_mutex_t *forks)
{
	int	i;

	i = 0;
	if (str)
		printf("%s\n", str);
	pthread_mutex_destroy(&table->print_lock);
	pthread_mutex_destroy(&table->meal_lock);
	pthread_mutex_destroy(&table->dead_lock);
	while (i < table->philos[0].num_of_philos)
	{
		pthread_mutex_destroy(&forks[i]);
		i++;
	}
}

int	sleeping(t_philo *philo)
{
	print_philo("is sleeping", philo, philo->id);
	ft_usleep(philo->tt_s);
	return (1);
}

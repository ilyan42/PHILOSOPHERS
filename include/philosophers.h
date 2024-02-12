/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilyanbendib <ilyanbendib@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 13:14:31 by ilbendib          #+#    #+#             */
/*   Updated: 2024/02/11 17:09:46 by ilyanbendib      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>

// pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

typedef  struct  s_philo
 { 				 
	pthread_t philo;
	int 				meal_eat; 
	size_t 			last_meal_eat; 
	size_t 			time_to_die; 
	size_t 			time_to_eat; 
	size_t 			time_to_sleep; 
	size_t 			start_time; 
	int 				num_of_philos; 
	int 				num_times_to_eat; 
	int 				*dead; 
	pthread_mutex_t 	*r_fork; 
	pthread_mutex_t 	*l_fork; 
	pthread_mutex_t 	*write_lock; 
	pthread_mutex_t 	*dead_lock; 
	pthread_mutex_t 	*meal_lock; 
} t_philo; 

typedef  struct  s_program
 { 
	int 				dead_flag; 
	pthread_mutex_t 	dead_lock; 
	pthread_mutex_t 	repas_lock; 
	pthread_mutex_t 	write_lock; 
	t_philo *philos; 
} t_programme ;

int ft_init_param(t_philo *philo, char **av);
void routine(t_philo *philo);

#endif
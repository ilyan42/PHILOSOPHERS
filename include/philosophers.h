/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilyanbendib <ilyanbendib@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 13:14:31 by ilbendib          #+#    #+#             */
/*   Updated: 2024/02/21 15:37:54 by ilyanbendib      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>

#define PHILO_MAX 300

typedef struct s_philo
{
	pthread_t		thread;
	int				id;
	int				eating;
	int				meals_eaten;
	size_t			last_meal;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	size_t			start_time;
	int				num_of_philos;
	int				num_times_to_eat;
	int				dead;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*print_lock;
	pthread_mutex_t	*dead_lock;
	pthread_mutex_t	*meal_lock;
}					t_philo;

typedef struct s_program
{
	int				dead_flag;
	pthread_mutex_t	dead_lock;
	pthread_mutex_t	meal_lock;
	pthread_mutex_t print_lock;
	t_philo			*philos;
}					t_program;

/********FT_INIT********/

void		ft_init_args(t_philo *philo, char **av);
int	creat_philo(t_program *program, pthread_mutex_t *forks);


/********FT_UTILS********/

int		ft_atoi(char *str);

/********FT_ROUTINE_PHILO********/

size_t	get_current_time(void);
int		ft_usleep(size_t milliseconds);
int		sleeping(t_philo *philo);
void	*routine(void *arg);

/********FT_ERROR_MSG********/

void	ft_error_msg(char *msg);


#endif
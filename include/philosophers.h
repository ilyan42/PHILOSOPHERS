/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilbendib <ilbendib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 13:14:31 by ilbendib          #+#    #+#             */
/*   Updated: 2024/03/08 17:29:43 by ilbendib         ###   ########.fr       */
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
	int				*dead;
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

void	ft_init_args(t_philo *philo, char **av);
void	ft_init_philos(t_philo *philos, t_program *program, pthread_mutex_t *forks, char **argv);
int		ft_creat_thread_philo(t_program *program, pthread_mutex_t *forks);
void	ft_init_param(t_program *program, t_philo *philos);
void	ft_init_forks(pthread_mutex_t *forks, int num_of_philos);

/********FT_UTILS********/

int		ft_atoi(char *str);
void	destroy_mutex_init(char *msg, t_program *program, pthread_mutex_t *forks);
void	print_philo(char *msg, t_philo *philo, int id);
size_t	get_current_time(void);
int	ft_usleep(size_t time);

/********FT_ROUTINE_PHILO********/

void	*routine(void *arg);
int		sleeping(t_philo *philo);
void	think(t_philo *philo);
void	take_a_fork(t_philo *philo);

/********FT_DEATH_PHILO********/

int		check_died_flg(t_philo *philo);
int		check_if_dead(t_philo *philos);
int		check_if_all_ate(t_philo *philos);
int		philosopher_dead(t_philo *philo, size_t time_to_die);
void	*loop_dead(void *arg);

/********FT_ERROR_MSG********/

void	ft_error_msg(char *msg);


#endif
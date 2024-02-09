/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilyanbendib <ilyanbendib@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 13:15:41 by ilbendib          #+#    #+#             */
/*   Updated: 2024/02/09 12:01:47 by ilyanbendib      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void *philo(void *arg)
{
	int i = 0;
	char *str = "Hello from philosopher number 1";
	
	pthread_mutex_lock(&mutex);
	while (i < 31)
	{
		printf("%c", str[i]);
		usleep(10000);
		i++;
	}
	pthread_mutex_unlock(&mutex);
	printf("\n");
	return (arg);
}

void *philo2(void *arg)
{
	int i = 0;
	char *str = "Hello from philosopher number 2";
	
	pthread_mutex_lock(&mutex);
	while (i < 31)
	{
		printf("%c", str[i]);
		usleep(10000);
		i++;
	}
	pthread_mutex_unlock(&mutex);
	printf("\n");
	return (arg);
}

int main(void)
{
	pthread_t philosophers;
	pthread_t philosophers2;
	
	pthread_create(&philosophers, NULL, philo, NULL);
	pthread_create(&philosophers2, NULL, philo2, NULL);
	
	pthread_join(philosophers, NULL);
	pthread_join(philosophers2, NULL);
	pthread_mutex_destroy(&mutex);
	return 0;
}


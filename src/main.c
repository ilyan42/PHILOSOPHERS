/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilbendib <ilbendib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 13:15:41 by ilbendib          #+#    #+#             */
/*   Updated: 2024/02/12 18:39:04 by ilbendib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void ft_error_msg(char *msg)
{
    printf("Error: %s\n", msg);
    exit(EXIT_FAILURE);
}

int main(int ac, char **av)
{
	t_philo philo;

	if (ac != 6)
        ft_error_msg("wrong number of arguments");
	if (ft_init_param(&philo, av) == 0)
        ft_error_msg("wrong arguments");
	if (creat_philo(&philo) == 0)
	        ft_error_msg("failed to create philosophers");
	return 0;
}



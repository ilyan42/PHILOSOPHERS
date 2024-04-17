/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_args.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilbendib <ilbendib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 11:27:29 by ilbendib          #+#    #+#             */
/*   Updated: 2024/03/29 12:06:03 by ilbendib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

static int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (i == n)
	{
		return (0);
	}
	while (i < (unsigned int)n - 1 && (s1[i] || s2[i]) && s1[i] == s2[i])
	{
		i++;
	}
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

static size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
	{
		i++;
	}
	return (i);
}

static int	check_int(char *arg, int *err, int indice)
{
	long int	number;
	char		*str;

	number = ft_atoi(arg, err);
	if (number > 200 && indice == 1)
	{
		*err = 1;
		return (0);
	}
	str = ft_itoa(number);
	if (!ft_strncmp(str, arg, ft_strlen(arg)))
		return (free(str), 0);
	*err = 1;
	return (free(str), 1);
}

int	check_args(char *argv[])
{
	int			err;
	int			i;
	int			number;

	i = 1;
	err = 0;
	while (argv[i])
	{
		number = ft_atoi(argv[i], &err);
		if (number <= 0 && i != 5)
			err = 1;
		if (number < 0 && i == 5)
			err = 1;
		check_int(argv[i], &err, i);
		if (err == 1)
		{
			printf("Wrong arguments\n");
			return (0);
		}
		i++;
	}
	return (1);
}

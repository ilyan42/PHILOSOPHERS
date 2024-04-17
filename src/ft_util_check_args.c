/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_util_check_args.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilbendib <ilbendib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 11:51:28 by ilbendib          #+#    #+#             */
/*   Updated: 2024/03/26 11:27:54 by ilbendib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

static long int	ft_chartoint(char *str, int sign)
{
	long int	output;

	output = 0;
	while (*str >= '0' && *str <= '9')
	{
		output = output * 10 + (*str - '0');
		if (output < 0)
		{
			if (sign)
				return (0);
			else
				return (-1);
		}
		str++;
	}
	if (sign)
		return (-output);
	return (output);
}

long int	ft_atoi(const char *str, int *error)
{
	int		sign;
	char	*ptr;

	ptr = (char *)str;
	sign = 0;
	while (*ptr == ' ' || *ptr == '\n' || *ptr == '\t' || *ptr == '\v'
		|| *ptr == '\f' || *ptr == '\r')
		ptr++;
	if (*ptr == '-' || *ptr == '+')
	{
		if (*ptr == '-')
			sign = 1;
		ptr++;
	}
	if (*ptr >= '0' && *ptr <= '9')
		return (ft_chartoint(ptr, sign));
	*error = 1;
	return (0);
}

static int	countnum(int n)
{
	size_t			i;
	unsigned int	nb;

	i = 0;
	if (n < 0)
	{
		nb = -n;
		i++;
	}
	else
		nb = n;
	while (nb > 9)
	{
		nb /= 10;
		i++;
	}
	return (i + 1);
}

static void	ft_putnbr(long int nb, char *str, size_t *i)
{
	unsigned long int	absolut;

	if (nb < 0)
	{
		absolut = -nb;
		str[*i] = '-';
		*i += 1;
	}
	else
		absolut = nb;
	if (absolut > 9)
	{
		ft_putnbr(absolut / 10, str, i);
	}
	str[*i] = absolut % 10 + '0';
	*i += 1;
}

char	*ft_itoa(long int n)
{
	int		count;
	char	*str;
	size_t	i;

	i = 0;
	count = countnum(n);
	str = (char *)malloc((count + 1) * sizeof(char));
	if (!str)
		return (NULL);
	ft_putnbr(n, str, &i);
	str[count] = '\0';
	return (str);
}

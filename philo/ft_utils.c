/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kahmada <kahmada@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 17:00:57 by kahmada           #+#    #+#             */
/*   Updated: 2024/09/25 12:44:27 by kahmada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	error(void)
{
	write(2, "ERROR\n", 6);
}

void	ft_usleep(long time_in_ms, t_table *table)
{
	long	start_time;

	start_time = get_time_in_ms();
	while (get_time_in_ms() - start_time < time_in_ms && !ft_end(table))
	{
		usleep(200);
	}
}

long	ft_atoi(char *s)
{
	long	result;
	int		signe;
	int		i;

	i = 0;
	result = 0;
	signe = 1;
	while (*s == ' ' || (*s >= 9 && *s <= 13))
		s++;
	if ((*s) == '-' || (*s) == '+')
	{
		signe = 1 - 2 * (*s++ == '-');
		i++;
	}
	while (*s >= '0' && *s <= '9')
	{
		if (*s != '0' && *(s + 1) != '0')
			i++;
		if (i > 11)
			return (LONG_MAX);
		result = result * 10 + (*s++ - '0');
	}
	return (signe * result);
}

static int	ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
		return (1);
	return (0);
}

int	is_not_valid_arg(char *str)
{
	if (*str == '\0')
		return (1);
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '\0')
		return (1);
	if (*str == '-')
		return (1);
	if (*str == '+')
		str++;
	if (*str == '\0')
		return (1);
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (1);
		str++;
	}
	return (0);
}

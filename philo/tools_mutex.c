/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_mutex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kahmada <kahmada@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 20:35:04 by kahmada           #+#    #+#             */
/*   Updated: 2024/09/25 09:41:23 by kahmada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_table(t_table **table, int ac, char **av)
{
	*table = malloc(sizeof(t_table));
	if (!*table)
	{
		error();
		return (0);
	}
	if (parcing(ac, av) == 0)
	{
		if (table && *table)
			free(*table);
		error();
		return (0);
	}
	init_args(*table, ac, av);
	return (1);
}

void	init_mutexes(t_table *table)
{
	if (pthread_mutex_init(&table->meal_check, NULL))
	{
		free(table);
		error();
		return ;
	}
	if (pthread_mutex_init(&table->print, NULL))
	{
		pthread_mutex_destroy(&table->meal_check);
		free(table);
		error();
		return ;
	}
}

void	init_philosophers(t_table *table)
{
	if (initialize_philosophers(table) == 0)
	{
		pthread_mutex_destroy(&table->print);
		pthread_mutex_destroy(&table->meal_check);
		free(table);
		error();
		return ;
	}
}

void	start_monitoring(t_table *table)
{
	pthread_t	monitor_thread;

	if (pthread_create(&monitor_thread, NULL, monitor_philo, table) != 0)
	{
		pthread_mutex_destroy(&table->print);
		pthread_mutex_destroy(&table->meal_check);
		destroy_fork(table);
		free(table->philos);
		free(table);
		error();
		return ;
	}
	if (pthread_join(monitor_thread, NULL))
	{
		pthread_mutex_destroy(&table->print);
		pthread_mutex_destroy(&table->meal_check);
		destroy_fork(table);
		free(table->philos);
		free(table);
		error();
		return ;
	}
}

void	start_threads(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->philo_nbr)
	{
		if (pthread_join(table->philos[i].thread_id, NULL))
		{
			pthread_mutex_destroy(&table->print);
			pthread_mutex_destroy(&table->meal_check);
			pthread_mutex_destroy(&table->philos[i].fork);
			free(table->philos);
			free(table);
			error();
			return ;
		}
		i++;
	}
}

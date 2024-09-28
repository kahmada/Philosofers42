/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kahmada <kahmada@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 18:38:25 by kahmada           #+#    #+#             */
/*   Updated: 2024/09/25 14:27:21 by kahmada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_end_simulation(t_table *table)
{
	int	end_simulation;

	pthread_mutex_lock(&table->meal_check);
	end_simulation = table->end_simulation;
	pthread_mutex_unlock(&table->meal_check);
	return (end_simulation);
}

int	check_died(t_table *table, t_philo *philo)
{
	int	i;

	i = 0;
	pthread_mutex_lock(&table->meal_check);
	if (get_time_in_ms() - philo->last_meals_time > table->time_to_die)
		i = 1;
	pthread_mutex_unlock(&table->meal_check);
	return (i);
}

bool	check_all_philos(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->philo_nbr)
	{
		if (check_died(table, &table->philos[i]))
		{
			write_message(table, table->philos[i].id, "died");
			pthread_mutex_lock(&table->meal_check);
			table->end_simulation = true;
			pthread_mutex_unlock(&table->meal_check);
			return (true);
		}
		i++;
	}
	return (false);
}

void	*monitor_philo(void *arg)
{
	t_table	*table;

	table = (t_table *)arg;
	while (!ft_end(table))
	{
		if (check_all_philos(table))
			return (NULL);
		if (table->nbr_limit_meals != -1)
			check_eat(table);
	}
	return (NULL);
}

int	main(int ac, char **av)
{
	t_table	*table;

	if (!init_table(&table, ac, av))
		return (0);
	init_mutexes(table);
	init_philosophers(table);
	start_simulation(table);
	start_monitoring(table);
	start_threads(table);
	return (cleanup(table), 0);
}

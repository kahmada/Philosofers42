/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filo_func.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kahmada <kahmada@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 15:26:55 by kahmada           #+#    #+#             */
/*   Updated: 2024/09/25 13:22:52 by kahmada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	check_eat(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->philo_nbr)
	{
		pthread_mutex_lock(&table->meal_check);
		if (table->philos[i].meals_counter < table->nbr_limit_meals)
			break ;
		pthread_mutex_unlock(&table->meal_check);
		i++;
	}
	pthread_mutex_unlock(&table->meal_check);
	if (i == table->philo_nbr)
	{
		pthread_mutex_lock(&table->meal_check);
		table->end_simulation = true;
		pthread_mutex_unlock(&table->meal_check);
	}
}

void	cleanup(t_table *table)
{
	int	i;

	i = 0;
	destroy_fork(table);
	pthread_mutex_destroy(&table->meal_check);
	pthread_mutex_destroy(&table->print);
	free(table->philos);
	free(table);
}

int	ft_end(t_table *table)
{
	int	end;

	pthread_mutex_lock(&table->meal_check);
	end = table->end_simulation;
	pthread_mutex_unlock(&table->meal_check);
	return (end);
}

void	eat(t_philo *philo, t_table *table)
{
	write_message(philo->table, philo->id, "is eating");
	pthread_mutex_lock(&table->meal_check);
	philo->last_meals_time = get_time_in_ms();
	philo->meals_counter++;
	pthread_mutex_unlock(&table->meal_check);
	ft_usleep(philo->table->time_to_eat, table);
}

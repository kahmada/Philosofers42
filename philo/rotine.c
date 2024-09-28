/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotine.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kahmada <kahmada@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 15:14:37 by kahmada           #+#    #+#             */
/*   Updated: 2024/09/25 09:40:19 by kahmada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	take_forks(t_philo *philo)
{
	pthread_mutex_lock(&philo->fork);
	write_message(philo->table, philo->id, "has taken a fork");
	pthread_mutex_lock(&philo->table->philos[(philo->id + 1) % \
	philo->table->philo_nbr].fork);
	write_message(philo->table, philo->id, "has taken a fork");
}

void	put_forks(t_philo *philo)
{
	pthread_mutex_unlock(&philo->fork);
	pthread_mutex_unlock(&philo->table->philos[(philo->id + 1) \
	% philo->table->philo_nbr].fork);
}

void	write_message(t_table *table, int philoid, char *str)
{
	pthread_mutex_lock(&(table->print));
	usleep(10);
	if (!ft_end(table))
	{
		printf("%ld ", get_time_in_ms() - table->start_t);
		printf("%d ", philoid + 1);
		printf("%s\n", str);
	}
	pthread_mutex_unlock(&(table->print));
}

void	handle_single_philosopher(t_philo *philo)
{
	t_table	*table;

	table = philo->table;
	write_message(table, philo->id, "has taken a fork");
	ft_usleep(table->time_to_die, table);
	write_message(table, philo->id, "died");
	table->end_simulation = true;
}

void	*philosopher_routine(void *arg)
{
	t_philo	*philo;
	t_table	*table;

	philo = (t_philo *)arg;
	table = philo->table;
	if (table->philo_nbr == 1)
	{
		handle_single_philosopher(philo);
		return (NULL);
	}
	if (philo->id % 2 == 0)
		ft_usleep(table->time_to_eat, table);
	while (!ft_end(table))
	{
		take_forks(philo);
		eat(philo, table);
		put_forks(philo);
		write_message(table, philo->id, "is sleeping");
		ft_usleep(philo->table->time_to_sleep, table);
		write_message(table, philo->id, "is thinking");
	}
	return (NULL);
}

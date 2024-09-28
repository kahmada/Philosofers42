/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kahmada <kahmada@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 15:21:45 by kahmada           #+#    #+#             */
/*   Updated: 2024/09/25 10:41:36 by kahmada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_args(t_table *table, int ac, char **av)
{
	table->philo_nbr = ft_atoi(av[1]);
	table->time_to_die = ft_atoi(av[2]);
	table->time_to_eat = ft_atoi(av[3]);
	table->time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		table->nbr_limit_meals = ft_atoi(av[5]);
	else
		table->nbr_limit_meals = -1;
}

void	start_simulation(t_table *table)
{
	int	i;

	i = 0;
	table->end_simulation = false;
	table->start_t = get_time_in_ms();
	while (i < table->philo_nbr)
	{
		if (pthread_create(&table->philos[i].thread_id, NULL, \
		philosopher_routine, &table->philos[i]) != 0)
		{
			free(table);
			free(table->philos);
			error();
			return ;
		}
		i++;
	}
}

void	destroy_forks_mutex(t_table *table, int i)
{
	while (--i >= 0)
	{
		pthread_mutex_destroy(&table->philos[i].fork);
	}
}

int	initialize_philosophers(t_table *table)
{
	t_philo	*philo;
	int		i;

	table->philos = malloc(sizeof(t_philo) * table->philo_nbr);
	if (!table->philos)
		return (0);
	i = 0;
	while (i < table->philo_nbr)
	{
		philo = &table->philos[i];
		philo->id = i;
		table->start_t = 0;
		philo->meals_counter = 0;
		philo->last_meals_time = get_time_in_ms();
		philo->table = table;
		if (pthread_mutex_init(&philo->fork, NULL) != 0)
		{
			destroy_forks_mutex(table, i);
			return (free(table->philos), 0);
		}
		i++;
	}
	return (1);
}

int	parcing(int ac, char **av)
{
	int	i;

	i = 1;
	if (ac < 5 || ac > 6)
		return (0);
	while (i < ac)
	{
		if (is_not_valid_arg(av[i]))
			return (0);
		i++;
	}
	if (ft_atoi(av[1]) == 0)
		return (0);
	if (av[5] && ft_atoi(av[5]) == 0)
		return (0);
	if (ft_atoi(av[2]) > INT_MAX || \
	ft_atoi(av[3]) > INT_MAX || ft_atoi(av[4]) > INT_MAX)
		return (0);
	return (1);
}

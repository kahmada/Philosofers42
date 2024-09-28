/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kahmada <kahmada@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 18:38:28 by kahmada           #+#    #+#             */
/*   Updated: 2024/09/25 14:31:06 by kahmada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>
# include <sys/time.h>
# include <stdio.h>
# include <limits.h>
# include <pthread.h>

typedef struct s_table
{
	long			philo_nbr;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long			nbr_limit_meals;
	long			start_t;
	bool			end_simulation;
	struct s_philo	*philos;
	pthread_mutex_t	meal_check;
	pthread_mutex_t	print;
}	t_table;

typedef struct s_philo
{
	int				id;
	long			meals_counter;
	long			last_meals_time;
	pthread_mutex_t	fork;
	pthread_t		thread_id;
	t_table			*table;
}	t_philo;
void	ft_usleep(long time_in_ms, t_table *table);
void	cleanup(t_table *table);
int		ft_end(t_table *table);
void	write_message(t_table *table, int philoid, char *str);
void	eat(t_philo *philo, t_table *table);
long	ft_atoi(char *s);
int		is_not_valid_arg(char *str);
void	start_simulation(t_table *table);
int		initialize_philosophers(t_table *table);
void	error(void);
int		parcing(int ac, char **av);
void	*monitor_philo(void *arg);
void	*philosopher_routine(void *arg);
void	check_eat(t_table *table);
void	init_args(t_table *table, int ac, char **av);
long	get_time_in_ms(void);
void	start_threads(t_table *table);
void	start_monitoring(t_table *table);
void	init_philosophers(t_table *table);
void	init_mutexes(t_table *table);
int		init_table(t_table **table, int ac, char **av);
void	destroy_fork(t_table *table);
#endif
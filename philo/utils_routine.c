/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zelabbas <zelabbas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 11:15:37 by zelabbas          #+#    #+#             */
/*   Updated: 2024/02/04 15:12:56 by zelabbas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_increment_nbr(pthread_mutex_t *mutex, long *value, t_data *table)
{
	mutex_handle_safely(mutex, LOCK, table);
	(*value)++;
	mutex_handle_safely(mutex, UNLOCK, table);
}

void	*ft_one_philo(void	*arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (!get_bool(&philo->all_data->mutex_table,
			&philo->all_data->all_philo_ready, philo->all_data))
				;
	ft_increment_nbr(&philo->all_data->mutex_table,
		&philo->all_data->nbr_ranning, philo->all_data);
	set_value(&philo->philo_mutex, &philo->last_time_eat,
		get_time(MILLISECONDS, philo->all_data), philo->all_data);
	ft_status_philo(TAKE_FST_F, philo);
	while (!simulation_is_finished(philo->all_data))
		usleep(200);
	return (NULL);
}

void	*routine(void *arg)
{
	t_philo	*ptr_philo;

	ptr_philo = (t_philo *)arg;
	while (!get_bool(&ptr_philo->all_data->mutex_table,
			&ptr_philo->all_data->all_philo_ready, ptr_philo->all_data))
				;
	ft_increment_nbr(&ptr_philo->all_data->mutex_table,
		&ptr_philo->all_data->nbr_ranning, ptr_philo->all_data);
	set_value(&ptr_philo->philo_mutex, &ptr_philo->last_time_eat,
		get_time(MILLISECONDS, ptr_philo->all_data), ptr_philo->all_data);
	while (!simulation_is_finished(ptr_philo->all_data))
	{
		if (ptr_philo->full)
			break ;
		ft_eat(ptr_philo);
		ft_rot_sleep(ptr_philo);
		ft_think(ptr_philo);
	}
	return (NULL);
}

bool	ft_philo_die(t_philo *philo)
{
	long	time;
	long	time_die;

	if (get_bool(&philo->philo_mutex, &philo->is_eating, philo->all_data))
		return (false);
	if (get_bool(&philo->philo_mutex, &philo->full, philo->all_data))
		return (false);
	time = get_time(MILLISECONDS, philo->all_data) - get_value(
			&philo->philo_mutex, &philo->last_time_eat, philo->all_data);
	time_die = philo->all_data->time_to_die / 1e3;
	if (time > time_die)
		return (true);
	return (false);
}

void	*ft_inspector(void	*arg)
{
	int		i;
	t_data	*table;

	table = (t_data *)arg;
	while (!ft_wait_threads(&table->mutex_table,
			&table->nbr_ranning, table->nbr_philo, table))
				;
	while (!simulation_is_finished(table))
	{
		usleep(1500);
		i = -1;
		while (++i < table->nbr_philo && !simulation_is_finished(table))
		{
			if (ft_philo_die(table->table_philos + i))
			{
				set_bool(&table->mutex_table, &table->end_simulation,
					true, table);
				ft_status_philo(DIED, table->table_philos + i);
			}
		}
	}
	return (NULL);
}

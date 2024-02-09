/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zelabbas <zelabbas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 10:56:49 by zelabbas          #+#    #+#             */
/*   Updated: 2024/02/05 12:57:03 by zelabbas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_philos(t_data *table)
{
	int		i;
	t_philo	*ptr_philo;

	i = -1;
	while (++i < table->nbr_philo)
	{
		ptr_philo = table->table_philos + i;
		ft_init_attr_philo(ptr_philo, table, i);
		if (!mutex_handle_safely(&ptr_philo->philo_mutex, INIT, table))
			return (0);
		table->n_mtx_ph++;
		if ((ptr_philo->id % 2) == 0)
		{
			ptr_philo->first_fork = &table->table_forks[i];
			ptr_philo->second_fork = &table->table_forks[
				(i + 1) % table->nbr_philo];
		}
		else
		{
			ptr_philo->first_fork = &table->table_forks[
				(i + 1) % table->nbr_philo];
			ptr_philo->second_fork = &table->table_forks[i];
		}
	}
	return (1);
}

int	ft_check_data_allocate(t_data *table)
{
	int	i;

	i = -1;
	if (!mutex_handle_safely(&table->mutex_table, INIT, table))
		return (0);
	table->n_mtx_t++;
	if (!mutex_handle_safely(&table->mutex_write, INIT, table))
		return (0);
	table->n_mtx_t++;
	while (++i < table->nbr_philo)
	{
		if (!mutex_handle_safely(&table->table_forks[i].fork, INIT, table))
			return (0);
		table->table_forks[i].id_fork = i;
		table->n_mtx_t++;
	}
	if (!init_philos(table))
		return (0);
	return (1);
}

int	ft_data_allocate(t_data *table)
{
	table->n_mtx_ph = 0;
	table->n_mtx_t = 0;
	table->table_philos = NULL;
	table->table_philos = allocate_memory_safely(
			sizeof(t_philo) * table->nbr_philo, table);
	if (!table->table_philos)
		return (0);
	table->table_forks = allocate_memory_safely(
			sizeof(t_fork) * table->nbr_philo, table);
	if (!table->table_forks)
		return (0);
	if (!ft_check_data_allocate(table))
		return (0);
	return (1);
}

int	init_table(t_data *table, char **av)
{
	table->nbr_philo = ft_atoi(*(av));
	if (!table->nbr_philo)
	{
		printf("0 philos !\n");
		return (0);
	}
	table->time_to_die = ft_atoi(*(av + 1)) * 1e3;
	table->time_to_eat = ft_atoi(*(av + 2)) * 1e3;
	table->time_to_sleep = ft_atoi(*(av + 3)) * 1e3;
	if (*(av + 4))
		table->nbr_eat_meals = ft_atoi(*(av + 4));
	else
		table->nbr_eat_meals = -1;
	table->end_simulation = false;
	if (!ft_data_allocate(table))
		return (0);
	table->all_philo_ready = false;
	table->nbr_ranning = 0;
	return (1);
}

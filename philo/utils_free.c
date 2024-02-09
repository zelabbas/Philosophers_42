/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zelabbas <zelabbas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 15:28:10 by zelabbas          #+#    #+#             */
/*   Updated: 2024/02/02 11:39:32 by zelabbas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_clean_table(t_data *table)
{
	t_philo	*p_philo;
	int		i;

	i = -1;
	while (++i < table->nbr_philo)
	{
		p_philo = table->table_philos + i;
		mutex_handle_safely(&table->table_forks[i].fork, DESTROY, table);
		mutex_handle_safely(&p_philo->philo_mutex, DESTROY, table);
	}
	mutex_handle_safely(&table->mutex_table, DESTROY, table);
	mutex_handle_safely(&table->mutex_write, DESTROY, table);
	free(table->table_forks);
	free(table->table_philos);
}

void	ft_free_tables(t_data *table)
{
	free(table->table_philos);
	free(table->table_forks);
}

void	ft_destroy_clean(t_data *table, int n)
{
	if (n == 1)
	{
		mutex_handle_safely(&table->mutex_table, DESTROY, table);
		ft_free_tables(table);
	}
	else if (n == 2)
	{
		mutex_handle_safely(&table->mutex_table, DESTROY, table);
		mutex_handle_safely(&table->mutex_write, DESTROY, table);
		ft_free_tables(table);
	}
}

void	ft_destroy_cleanv2(t_data *table)
{
	int	i;

	i = -1;
	while (++i < table->n_mtx_t - 2)
		mutex_handle_safely(&table->table_forks[i].fork, DESTROY, table);
	i = -1;
	if (table->n_mtx_ph != 0)
	{
		while (++i < table->n_mtx_ph)
			mutex_handle_safely(&table->table_philos[i].philo_mutex,
				DESTROY, table);
	}
	ft_destroy_clean(table, 2);
}

void	ft_free(t_data *table)
{
	if (table->n_mtx_t == 0)
		ft_free_tables(table);
	else if (table->n_mtx_t == 1 || table->n_mtx_t == 2)
		ft_destroy_clean(table, table->n_mtx_t);
	else if (table->n_mtx_t > 2)
		ft_destroy_cleanv2(table);
}

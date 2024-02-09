/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getters_setters.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zelabbas <zelabbas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 11:36:31 by zelabbas          #+#    #+#             */
/*   Updated: 2024/02/02 12:33:20 by zelabbas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	get_bool(pthread_mutex_t *mutex, bool *value, t_data *table)
{
	bool	res;

	mutex_handle_safely(mutex, LOCK, table);
	res = *value;
	mutex_handle_safely(mutex, UNLOCK, table);
	return (res);
}

void	set_bool(pthread_mutex_t *mutex, bool *dest, bool value, t_data *table)
{
	mutex_handle_safely(mutex, LOCK, table);
	*dest = value;
	mutex_handle_safely(mutex, UNLOCK, table);
}

void	set_value(pthread_mutex_t *mutex, long *dest, long value, t_data *table)
{
	mutex_handle_safely(mutex, LOCK, table);
	*dest = value;
	mutex_handle_safely(mutex, UNLOCK, table);
}

long	get_value(pthread_mutex_t *mutex, long *value, t_data *table)
{
	long	res;

	mutex_handle_safely(mutex, LOCK, table);
	res = *value;
	mutex_handle_safely(mutex, UNLOCK, table);
	return (res);
}

bool	simulation_is_finished(t_data *table)
{
	return (get_bool(&table->mutex_table, &table->end_simulation, table));
}

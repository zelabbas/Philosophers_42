/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wait_all_threads.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zelabbas <zelabbas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 11:18:54 by zelabbas          #+#    #+#             */
/*   Updated: 2024/02/03 11:14:02 by zelabbas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	ft_wait_threads(pthread_mutex_t *mutex,
						long *threads, long nbr_philos, t_data *table)
{
	bool	check;

	check = false;
	mutex_handle_safely(mutex, LOCK, table);
	if (*threads == nbr_philos)
		check = true;
	mutex_handle_safely(mutex, UNLOCK, table);
	return (check);
}

void	ft_init_attr_philo(t_philo *ptr_philo, t_data *table, int i)
{
	ptr_philo->id = i + 1;
	ptr_philo->full = false;
	ptr_philo->all_data = table;
	ptr_philo->counter_eat = 0;
	ptr_philo->is_eating = false;
}

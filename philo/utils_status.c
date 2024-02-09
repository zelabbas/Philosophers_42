/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_status.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zelabbas <zelabbas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 10:45:54 by zelabbas          #+#    #+#             */
/*   Updated: 2024/02/03 11:13:11 by zelabbas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_status_philo(int status, t_philo *philo)
{
	long	time_ms;

	if (philo->full)
		return ;
	mutex_handle_safely(&philo->all_data->mutex_write, LOCK, philo->all_data);
	time_ms = get_time(MILLISECONDS,
			philo->all_data) - philo->all_data->start_simulation;
	if (status == TAKE_FST_F && !simulation_is_finished(philo->all_data))
		printf("%ld %d has taken a fork\n", time_ms, philo->id);
	else if (status == TAKE_SCD_F && !simulation_is_finished(philo->all_data))
		printf("%ld %d has taken a fork\n", time_ms, philo->id);
	else if (status == EAT && !simulation_is_finished(philo->all_data))
		printf("%ld %d is eating\n", time_ms, philo->id);
	else if (status == THINK && !simulation_is_finished(philo->all_data))
		printf("%ld %d is thinking\n", time_ms, philo->id);
	else if (status == SLEEP && !simulation_is_finished(philo->all_data))
		printf("%ld %d is sleeping\n", time_ms, philo->id);
	else if (status == DIED)
		printf("%ld %d died\n", time_ms, philo->id);
	mutex_handle_safely(&philo->all_data->mutex_write, UNLOCK, philo->all_data);
}

void	ft_eat(t_philo *philo)
{
	mutex_handle_safely(&philo->first_fork->fork, LOCK, philo->all_data);
	ft_status_philo(TAKE_FST_F, philo);
	mutex_handle_safely(&philo->second_fork->fork, LOCK, philo->all_data);
	ft_status_philo(TAKE_SCD_F, philo);
	philo->counter_eat++;
	set_value(&philo->philo_mutex,
		&philo->last_time_eat, get_time(MILLISECONDS, philo->all_data),
		philo->all_data);
	ft_status_philo(EAT, philo);
	set_bool(&philo->philo_mutex, &philo->is_eating, true, philo->all_data);
	ft_sleep(philo->all_data->time_to_eat, philo->all_data);
	set_bool(&philo->philo_mutex, &philo->is_eating, false, philo->all_data);
	if (philo->counter_eat > 0
		&& philo->all_data->nbr_eat_meals == philo->counter_eat)
		set_bool(&philo->philo_mutex, &philo->full, true, philo->all_data);
	mutex_handle_safely(&philo->first_fork->fork, UNLOCK, philo->all_data);
	mutex_handle_safely(&philo->second_fork->fork, UNLOCK, philo->all_data);
}

void	ft_rot_sleep(t_philo *philo)
{
	ft_status_philo(SLEEP, philo);
	ft_sleep(philo->all_data->time_to_sleep, philo->all_data);
}

void	ft_think(t_philo *philo)
{
	long	t_eat;
	long	t_sleep;
	long	t_think;

	ft_status_philo(THINK, philo);
	if (philo->all_data->nbr_philo % 2)
	{
		t_eat = philo->all_data->time_to_eat;
		t_sleep = philo->all_data->time_to_sleep;
		t_think = (t_eat * 2) - t_sleep;
		if (t_think < 0)
			t_think = 0;
		ft_sleep(t_think * 0.20, philo->all_data);
	}
}

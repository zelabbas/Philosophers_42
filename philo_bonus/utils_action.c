/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_action.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zelabbas <zelabbas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 14:56:18 by zelabbas          #+#    #+#             */
/*   Updated: 2024/02/06 14:00:56 by zelabbas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	ft_death(t_data *table)
{
	ft_print(table, DIED);
}

void	ft_eat(t_data *table)
{
	sem_wait(table->forks);
	ft_print(table, TAKE_F);
	sem_wait(table->forks);
	ft_print(table, TAKE_F);
	ft_print(table, EAT);
	table->last_time_eat = get_time(MILLISECONDS);
	ft_sleep(table->ptr->time_to_eat + get_time(MILLISECONDS));
	table->times_eat++;
	sem_post(table->forks);
	sem_post(table->forks);
}

void	ft_sleeping(t_data *table)
{
	ft_print(table, SLEEP);
	ft_sleep(table->ptr->time_to_sleep + get_time(MILLISECONDS));
}

void	ft_think(t_data *table)
{
	ft_print(table, THINK);
}

void	ft_print(t_data *table, int n)
{
	const char	*tab_strings[] = {
		"has taken a fork", "is eating", "is sleeping",
		"is thinking", "died"};

	sem_wait(table->death);
	if (n == 4)
	{
		sem_wait(table->print);
		printf("%ld %d %s\n", get_time(MILLISECONDS) - table->ptr->start_time,
			table->id, tab_strings[n]);
		kill(0, SIGKILL);
	}
	sem_post(table->death);
	sem_wait(table->print);
	printf("%ld %d %s\n", get_time(MILLISECONDS) - table->ptr->start_time,
		table->id, tab_strings[n]);
	sem_post(table->print);
}

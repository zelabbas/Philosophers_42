/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_time.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zelabbas <zelabbas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 12:54:32 by zelabbas          #+#    #+#             */
/*   Updated: 2024/02/04 11:29:44 by zelabbas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_time(int t_option, t_data *table)
{
	t_time	tv;

	(void)table;
	if (gettimeofday(&tv, NULL))
	{
		printf("error in step get time!\n");
		return (0);
	}
	if (t_option == MILLISECONDS)
		return ((tv.tv_sec * 1e3) + (tv.tv_usec / 1e3));
	else if (t_option == MICROSECONDS)
		return ((tv.tv_sec * 1e6) + (tv.tv_usec));
	else
	{
		printf("Invalid time option!\n");
		return (0);
	}
}

void	ft_sleep(long time_to_sleep, t_data *table)
{
	long	start_time;
	long	is_passed;
	long	rem;

	start_time = get_time(MICROSECONDS, table);
	while (get_time(MICROSECONDS, table) - start_time < time_to_sleep)
	{
		if (simulation_is_finished(table))
			break ;
		is_passed = get_time(MICROSECONDS, table) - start_time;
		rem = time_to_sleep - is_passed;
		if (rem > 1e4)
			usleep(rem / 2);
		else
			while (get_time(MICROSECONDS, table) - start_time < time_to_sleep)
				;
	}
}

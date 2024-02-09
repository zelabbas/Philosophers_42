/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_time_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zelabbas <zelabbas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 20:48:06 by zelabbas          #+#    #+#             */
/*   Updated: 2024/02/02 14:53:46 by zelabbas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

long	get_time(int t_option)
{
	t_time	tv;

	if (gettimeofday(&tv, NULL))
	{
		printf("error in step get time!\n");
		exit(-1);
	}
	if (t_option == MILLISECONDS)
		return ((tv.tv_sec * 1e3) + (tv.tv_usec / 1e3));
	else if (t_option == MICROSECONDS)
		return ((tv.tv_sec * 1e6) + (tv.tv_usec));
	else
	{
		printf("Invalid time option!\n");
		exit(-1);
	}
}

void	ft_sleep(long time_to_sleep)
{
	long	time;

	time = get_time(MILLISECONDS);
	while (time_to_sleep - time > 5)
	{
		usleep(1000 * (time_to_sleep - time - 5));
		time = get_time(MILLISECONDS);
	}
	while (time_to_sleep > time)
		time = get_time(MILLISECONDS);
}

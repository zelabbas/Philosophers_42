/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_init_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zelabbas <zelabbas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 12:27:37 by zelabbas          #+#    #+#             */
/*   Updated: 2024/02/05 13:37:23 by zelabbas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	ft_init_args(t_arg *args, char **av)
{
	args->nbr_philos = ft_atoi(*av);
	if (!args->nbr_philos)
	{
		printf("0 philos raning!\n");
		exit(0);
	}
	args->time_to_die = ft_atoi(*(av + 1));
	args->time_to_eat = ft_atoi(*(av + 2));
	args->time_to_sleep = ft_atoi(*(av + 3));
	if (*(av + 4))
		args->nbr_meals = ft_atoi(*(av + 4));
	else
		args->nbr_meals = -1;
	if (!args->nbr_meals)
		exit(0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zelabbas <zelabbas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 15:41:29 by zelabbas          #+#    #+#             */
/*   Updated: 2024/02/05 14:47:28 by zelabbas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_creat_thread(t_data *table)
{
	int	i;

	i = -1;
	if (table->nbr_eat_meals == 0)
		return (0);
	else if (table->nbr_philo == 1)
	{
		if (!thread_handle_safly(&table->table_philos[0].id_philo,
				ft_one_philo, &table->table_philos[0], table))
			return (0);
	}
	else
	{
		while (++i < table->nbr_philo)
			if (!thread_handle_safly(&table->table_philos[i].id_philo,
					routine, &table->table_philos[i], table))
				return (0);
	}
	if (!thread_handle_safly(&table->inspector, ft_inspector, table, table))
		return (0);
	return (1);
}

int	ft_start(t_data *table)
{
	int	i;

	i = -1;
	table->step = CREAT;
	if (!ft_creat_thread(table))
		return (0);
	table->start_simulation = get_time(MILLISECONDS, table);
	set_bool(&table->mutex_table, &table->all_philo_ready, true, table);
	i = -1;
	table->step = JOIN;
	while (++i < table->nbr_philo)
		thread_handle_safly(&table->table_philos[i].id_philo,
			NULL, NULL, table);
	set_bool(&table->mutex_table, &table->end_simulation, true, table);
	thread_handle_safly(&table->inspector, NULL, NULL, table);
	return (1);
}

int	main(int ac, char **av)
{
	t_data	table;

	if (ac == 5 || ac == 6)
	{
		if (!check_arguments(av + 1))
		{
			printf("error in parsing !\n");
			return (0);
		}
		if (!init_table(&table, av + 1))
			return (0);
		if (!ft_start(&table))
		{
			ft_clean_table(&table);
			return (0);
		}
		ft_clean_table(&table);
	}
	else
		printf("error usage: nbr_philos t_die t_eat t_sleep nbr_meals\n");
	return (0);
}

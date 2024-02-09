/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zelabbas <zelabbas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 11:01:27 by zelabbas          #+#    #+#             */
/*   Updated: 2024/02/06 15:22:02 by zelabbas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	ft_error_creat_child(void)
{
	printf("error: faild to creat child proccess\n");
	kill(0, SIGKILL);
}

int	ft_start(t_data *table)
{
	if (table->times_eat >= table->ptr->nbr_meals && table->ptr->nbr_meals > 0)
		return (0);
	ft_eat(table);
	ft_sleeping(table);
	ft_think(table);
	return (1);
}

void	*routine_thread(void *arg)
{
	t_data	*table;

	table = (t_data *)arg;
	while (1)
	{
		usleep(1500);
		if (get_time(MILLISECONDS) - table->last_time_eat > table->time_die)
			ft_death(table);
		if (table->times_eat == table->ptr->nbr_meals)
			break ;
	}
	return (NULL);
}

void	*routine_philo(t_data *table)
{
	pthread_t	thread;

	table->time_die = table->ptr->time_to_die;
	table->last_time_eat = get_time(MILLISECONDS);
	pthread_create(&thread, NULL, routine_thread, (void *)table);
	while (ft_start(table))
		;
	pthread_join(thread, NULL);
	return (NULL);
}

int	main(int ac, char **av)
{
	t_data	table;
	t_arg	args;

	if (ac == 5 || ac == 6)
	{
		check_arguments(av + 1);
		ft_init_args(&args, (av + 1));
		args.start_time = get_time(MILLISECONDS);
		ft_creat_semphors(&table, &args);
		if (args.nbr_philos == 1)
			ft_one_philo(&table, av + 1);
		ft_creat_philo(&table, &args);
		sem_unlink("/forks");
		sem_unlink("/print");
		sem_unlink("/death");
	}
	else
		printf("error usage: nbr_philos t_die t_eat t_sleep nbr_meals\n");
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_init_creat.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zelabbas <zelabbas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 14:42:26 by zelabbas          #+#    #+#             */
/*   Updated: 2024/02/06 15:21:32 by zelabbas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	ft_one_philo(t_data *table, char **av)
{
	pid_t	pid;
	t_arg	args_child;

	pid = fork();
	if (pid == -1)
		ft_error_creat_child();
	args_child.start_time = get_time(MILLISECONDS);
	if (pid == 0)
	{
		ft_init_args(&args_child, av);
		sem_wait(table->forks);
		printf("%ld %d has taken a fork\n",
			get_time(MILLISECONDS) - args_child.start_time, 1);
		ft_sleep(args_child.time_to_die + get_time(MILLISECONDS));
		printf("%ld %d died\n",
			get_time(MILLISECONDS) - args_child.start_time, 1);
	}
	else
	{
		waitpid(pid, NULL, 0);
		sem_close(table->forks);
		sem_close(table->death);
		sem_close(table->print);
	}
	exit(0);
}

void	ft_creat_semphors(t_data *table, t_arg *arg)
{
	sem_unlink("/forks");
	sem_unlink("/print");
	sem_unlink("/death");
	table->forks = sem_open("/forks", O_CREAT, 0644, arg->nbr_philos);
	table->death = sem_open("/death", O_CREAT, 0644, 1);
	table->print = sem_open("/print", O_CREAT, 0644, 1);
}

void	ft_init_philo(t_data *table, t_arg *args, int i)
{
	table->id = i;
	table->times_eat = 0;
	table->ptr = args;
}

void	ft_wait_childs(t_arg *args)
{
	int	i;

	i = -1;
	while (++i < args->nbr_philos)
		waitpid(-1, NULL, 0);
}

void	ft_creat_philo(t_data *table, t_arg *args)
{
	int		i;
	pid_t	pid;

	i = -1;
	while (++i < args->nbr_philos)
	{
		pid = fork();
		if (pid == -1)
			ft_error_creat_child();
		if (pid == 0)
		{
			ft_init_philo(table, args, i + 1);
			routine_philo(table);
			return ;
		}
	}
	ft_wait_childs(args);
	sem_close(table->forks);
	sem_close(table->print);
	sem_close(table->death);
}

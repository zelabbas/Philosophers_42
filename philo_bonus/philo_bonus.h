/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zelabbas <zelabbas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 11:01:44 by zelabbas          #+#    #+#             */
/*   Updated: 2024/02/06 15:26:53 by zelabbas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <limits.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdbool.h>
# include <signal.h>
# include <semaphore.h>

typedef struct timeval	t_time;

// for options times
# define MICROSECONDS 0
# define MILLISECONDS 1

// status philo
# define TAKE_F 0
# define EAT	1
# define SLEEP	2
# define THINK	3
# define DIED	4

typedef struct s_arg
{
	long	nbr_philos;
	long	time_to_die;
	long	time_to_eat;
	long	time_to_sleep;
	long	nbr_meals;
	long	start_time;
}	t_arg;

typedef struct s_data
{
	t_arg	*ptr;
	int		id;
	long	time_die;
	long	last_time_eat;
	sem_t	*forks;
	sem_t	*death;
	sem_t	*print;
	int		times_eat;
}	t_data;

void	check_arguments(char **av);
long	ft_atoi(char *str);
void	ft_init_args(t_arg *args, char **av);
long	get_time(int t_option);
void	ft_sleep(long time_to_sleep);
void	ft_one_philo(t_data *table, char **av);
void	ft_creat_semphors(t_data *table, t_arg *arg);
void	ft_creat_philo(t_data *table, t_arg *args);
void	ft_error_creat_child(void);
void	ft_death(t_data *table);
void	ft_eat(t_data *table);
void	ft_sleeping(t_data *table);
void	ft_think(t_data *table);
void	*routine_philo(t_data *table);
void	ft_print(t_data *table, int n);

#endif
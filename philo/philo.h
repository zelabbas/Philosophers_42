/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zelabbas <zelabbas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 18:19:47 by zelabbas          #+#    #+#             */
/*   Updated: 2024/02/03 15:32:31 by zelabbas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <limits.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdbool.h>
# include <errno.h>

// mutex define
# define INIT 0
# define LOCK 1
# define UNLOCK 2
# define DESTROY 3
// thread define
# define CREAT 0
# define JOIN 1
# define DETACH 2
// time define
# define MICROSECONDS 0
# define MILLISECONDS 1

// status philo
# define TAKE_FST_F 0
# define TAKE_SCD_F 1
# define EAT		2
# define SLEEP		3
# define THINK		4
# define DIED		5

typedef struct s_data	t_data;
typedef struct timeval	t_time;

typedef struct s_fork
{
	pthread_mutex_t	fork;
	int				id_fork;
}	t_fork;

typedef struct s_philo
{
	int				id;
	t_fork			*first_fork;
	t_fork			*second_fork;
	bool			full;
	pthread_t		id_philo;
	long			counter_eat;
	long			last_time_eat;
	t_data			*all_data;
	bool			is_eating;
	pthread_mutex_t	philo_mutex;
}	t_philo;

struct	s_data
{
	long			nbr_philo;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long			nbr_eat_meals;
	t_fork			*table_forks;
	t_philo			*table_philos;
	pthread_mutex_t	mutex_table;
	pthread_mutex_t	mutex_write;
	bool			all_philo_ready;
	long			start_simulation;
	long			nbr_ranning;
	bool			end_simulation;
	pthread_t		inspector;
	int				n_mtx_t;
	int				n_mtx_ph;
	int				step;
};

int		check_arguments(char **av);
long	ft_atoi(char *str);
void	ft_error(char *str);
int		init_table(t_data *table, char **av);
void	*allocate_memory_safely(size_t bytes, t_data *table);
int		thread_handle_safly(pthread_t *thread,
			void *(*func)(void *), void *data, t_data *table);
int		mutex_handle_safely(pthread_mutex_t *mutex, int n, t_data *table);
bool	get_bool(pthread_mutex_t *mutex, bool *value, t_data *table);
void	set_bool(pthread_mutex_t *mutex, bool *dest, bool value, t_data *table);
void	set_value(pthread_mutex_t *mutex, long *dest,
			long value, t_data *table);
long	get_value(pthread_mutex_t *mutex, long *value, t_data *table);
bool	simulation_is_finished(t_data *table);
long	get_time(int t_option, t_data *table);
void	ft_sleep(long time_to_sleep, t_data *table);
void	ft_status_philo(int status, t_philo *philo);
void	ft_eat(t_philo *philo);
void	ft_rot_sleep(t_philo *philo);
void	ft_think(t_philo *philo);
bool	ft_wait_threads(pthread_mutex_t *mutex, long *threads,
			long nbr_philos, t_data *table);
void	*ft_one_philo(void	*arg);
void	*routine(void *arg);
void	*ft_inspector(void	*arg);
void	ft_free(t_data *table);
void	ft_clean_table(t_data *table);
void	ft_init_attr_philo(t_philo *ptr_philo, t_data *table, int i);

#endif
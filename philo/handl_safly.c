/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handl_safly.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zelabbas <zelabbas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 16:28:04 by zelabbas          #+#    #+#             */
/*   Updated: 2024/02/02 11:39:18 by zelabbas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	handl_mutex_error(int status, int n, t_data *table)
{
	if (!status)
		return (1);
	else if (EINVAL == status && (n == LOCK || n == UNLOCK))
		printf("The value specified by mutex is invalid.\n");
	else if (EINVAL == status && n == INIT)
		printf("The value specified by attr is invalid.\n");
	else if (EDEADLK == status)
		printf("A deadlock: thread blocked waiting for mutex.\n");
	else if (EPERM == status)
		printf(" The current thread does not hold a lock on mutex.\n");
	else if (ENOMEM == status)
		printf(" The process cannot allocate memory to create mutex.\n");
	else if (EBUSY == status)
		printf("Mutex is locked\n");
	else if (EINVAL == status && n == DESTROY)
		printf(" The value specified by mutex is invalid.\n");
	return (ft_free(table), 0);
}

int	mutex_handle_safely(pthread_mutex_t *mutex, int n, t_data *table)
{
	if (n == INIT)
	{
		if (!handl_mutex_error(pthread_mutex_init(mutex, NULL), n, table))
			return (0);
	}
	else if (n == LOCK)
	{
		if (!handl_mutex_error(pthread_mutex_lock(mutex), n, table))
			return (0);
	}
	else if (n == UNLOCK)
	{
		if (!handl_mutex_error(pthread_mutex_unlock(mutex), n, table))
			return (0);
	}
	else if (n == DESTROY)
	{
		if (!handl_mutex_error(pthread_mutex_destroy(mutex), n, table))
			return (0);
	}
	return (1);
}

int	handl_thread_error(int status, int n, t_data *table)
{
	if (!status)
		return (1);
	else if (n == CREAT && status == EINVAL)
		printf("The value specified by attr is invalid.\n");
	else if (status == EAGAIN)
		printf("NO resources to creat anohter thread.\n");
	else if (status == EPERM)
		printf(" The caller does not have appropriate permission\n");
	else if (EINVAL == status && (n == JOIN || n == DETACH))
		printf("join a thread that was not created as joinable.\n");
	else if (status == ESRCH)
		printf("No thread could be found corresponding to that thread ID\n");
	else if (status == EDEADLK)
		printf("deadlock was detected or the value of thread..(lock man)\n");
	return (ft_free(table), 0);
}

int	thread_handle_safly(pthread_t *thread,
			void *(*func)(void *), void *data, t_data *table)
{
	int	n;

	n = table->step;
	if (n == CREAT)
	{
		if (!handl_thread_error(pthread_create(thread, NULL, func, data),
				n, table))
			return (0);
	}
	else if (n == JOIN)
	{
		if (!handl_thread_error(pthread_join(*thread, NULL), n, table))
			return (0);
	}
	else if (n == DETACH)
	{
		if (!handl_thread_error(pthread_detach(*thread), n, table))
			return (0);
	}
	return (1);
}

void	*allocate_memory_safely(size_t bytes, t_data *table)
{
	void	*ptr;

	ptr = malloc(bytes);
	if (!ptr)
	{
		if (table->table_philos)
			free(table->table_philos);
		printf("faild to allocate memory!");
		return (NULL);
	}
	return (ptr);
}

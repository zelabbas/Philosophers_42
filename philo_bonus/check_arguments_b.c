/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_arguments_b.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zelabbas <zelabbas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 18:19:29 by zelabbas          #+#    #+#             */
/*   Updated: 2024/02/03 20:25:01 by zelabbas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	ft_error(char *str)
{
	write(1, str, ft_strlen(str));
	exit(-1);
}

void	check_syntax(char *str)
{
	while (*str)
	{
		if (!(*str >= '0' && *str <= '9') && *str != 32)
		{
			if (*str != '+' && *str != '-' && *str != 9)
				ft_error("error parssing:arg containe characters\n");
		}
		str++;
	}
}

void	check_arguments(char **av)
{
	int	i;
	int	j;
	int	check;

	i = 0;
	while (av[i])
	{
		check = 0;
		j = 0;
		if (!av[i][j])
			ft_error("null string\n");
		while (av[i][j])
		{
			if (av[i][j] != 32)
				check++;
			j++;
		}
		if (!check)
			ft_error("error parsing : just spaces in arg\n");
		check_syntax(av[i]);
		if (ft_atoi(av[i]) < 0 || ft_atoi(av[i]) > INT_MAX)
			ft_error("error parsing : value > INT_MAX or value < 0\n");
		i++;
	}
}

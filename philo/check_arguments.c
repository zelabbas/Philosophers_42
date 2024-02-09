/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_arguments.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zelabbas <zelabbas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 18:19:29 by zelabbas          #+#    #+#             */
/*   Updated: 2024/02/03 15:14:45 by zelabbas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_extract_nubmre(char **str, long *res)
{
	int		count;

	while (**str && **str == '0')
		(*str)++;
	count = 0;
	while (**str && (**str >= '0' && **str <= '9'))
	{
		*res = *res * 10 + (**str - 48);
		(*str)++;
		count++;
	}
	return (count);
}

int	check_syntax(char *str)
{
	while (*str)
	{
		if (!(*str >= '0' && *str <= '9') && *str != 32)
		{
			if (*str != '+' && *str != '-' && *str != 9)
				return (0);
		}
		str++;
	}
	return (1);
}

long	ft_atoi(char *str)
{
	int		sign;
	long	res;

	sign = 1;
	res = 0;
	while (*str && (*str == 32 || (*str >= 9 && *str <= 13)))
		str++;
	if (*str == '+')
		str++;
	else if (*str == '-')
	{
		sign *= -1;
		str++;
	}
	if (!(*str >= '0' && *str <= '9'))
		return (-1);
	if (ft_extract_nubmre(&str, &res) > 10)
		return (-1);
	if (*str && (*str != 32 && *str != 9))
		return (-1);
	return (res * sign);
}

int	ft_check(char *av)
{
	if (!check_syntax(av))
		return (0);
	if (ft_atoi(av) < 0 || ft_atoi(av) > INT_MAX)
		return (0);
	return (1);
}

int	check_arguments(char **av)
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
			return (0);
		while (av[i][j])
		{
			if (av[i][j] != 32)
				check++;
			j++;
		}
		if (!check)
			return (0);
		if (!ft_check(av[i]))
			return (0);
		i++;
	}
	return (1);
}

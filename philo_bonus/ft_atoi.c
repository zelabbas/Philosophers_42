/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zelabbas <zelabbas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 20:13:21 by zelabbas          #+#    #+#             */
/*   Updated: 2024/02/03 20:25:39 by zelabbas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

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

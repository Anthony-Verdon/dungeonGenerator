/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: averdon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 16:51:37 by averdon           #+#    #+#             */
/*   Updated: 2022/10/21 01:17:09 by averdon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

int	overflow(int number)
{
	if (number >= 0)
		return (-1);
	else
		return (0);
}

int	ft_atoi(const char *nptr)
{
	int		i;
	long	to_return;
	int		is_neg;

	i = 0;
	to_return = 0;
	is_neg = 1;
	while ((nptr[i] >= '\a' && nptr[i] <= '\r') || nptr[i] == ' ')
		i++;
	if (nptr[i] == '-')
	{
		i++;
		is_neg = -1;
	}
	else if (nptr[i] == '+')
		i++;
	while (nptr[i] != '\0' && nptr[i] >= '0' && nptr[i] <= '9')
	{
		to_return = to_return * 10 + (nptr[i] - 48);
		if (to_return * is_neg > INT_MAX || to_return * is_neg < INT_MIN)
			return (overflow(is_neg * to_return));
		i++;
	}
	return (to_return * is_neg);
}

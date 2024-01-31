/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_iterative_power.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: averdon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 14:15:13 by averdon           #+#    #+#             */
/*   Updated: 2022/10/05 13:04:38 by averdon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
long	ft_iterative_power(int nb, int power)
{
	long	nombre;

	nombre = nb;
	if (power == 0)
		return (1);
	else if (power < 0)
		return (0);
	while (power > 1)
	{
		nombre *= nb;
		power--;
	}
	return (nombre);
}

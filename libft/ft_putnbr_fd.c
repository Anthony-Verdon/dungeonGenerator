/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: averdon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 15:51:12 by averdon           #+#    #+#             */
/*   Updated: 2022/09/29 09:30:53 by averdon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	int	div;
	int	num_temp;

	div = 1;
	if (n < 0)
	{
		if (n == INT_MIN)
		{
			write(fd, "-2147483648", 11);
			return ;
		}
		write(fd, "-", 1);
		n = -n;
	}
	while (n / 10 >= div)
	{
		div = div * 10;
	}
	while (div >= 1)
	{
		num_temp = n / div + 48;
		write(fd, &num_temp, 1);
		n = n % div;
		div = div / 10;
	}
}

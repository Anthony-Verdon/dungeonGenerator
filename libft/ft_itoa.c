/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: averdon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 11:38:02 by averdon           #+#    #+#             */
/*   Updated: 2022/09/29 17:48:47 by averdon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

char	*create_min_char(void)
{
	char	*chr_number;
	char	*min_int;
	int		i;

	chr_number = malloc(12);
	if (!chr_number)
		return (NULL);
	min_int = "-2147483648";
	i = 0;
	while (i < 12)
	{
		chr_number[i] = min_int[i];
		i++;
	}
	return (chr_number);
}

char	*create_char(int div, int is_neg, int n, int num_digit)
{
	char	*chr_number;
	int		i;

	i = 0;
	chr_number = malloc(num_digit * sizeof(char) + 1);
	if (!chr_number)
		return (NULL);
	while (div != 0)
	{
		if (is_neg == 1 && i == 0)
			chr_number[i] = '-';
		else
		{
			chr_number[i] = n / div + 48;
			n = n % div;
			div = div / 10;
		}
		i++;
	}
	chr_number[i] = '\0';
	return (chr_number);
}

char	*ft_itoa(int n)
{
	int		div;
	int		num_digit;
	int		is_neg;

	div = 1;
	num_digit = 1;
	is_neg = 0;
	if (n < 0)
	{
		if (n == INT_MIN)
			return (create_min_char());
		num_digit++;
		n = n * -1;
		is_neg = 1;
	}
	while (n / 10 >= div)
	{
		div = div * 10;
		num_digit++;
	}
	return (create_char(div, is_neg, n, num_digit));
}

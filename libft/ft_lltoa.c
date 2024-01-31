/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lltoa.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: averdon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 16:46:03 by averdon           #+#    #+#             */
/*   Updated: 2023/01/05 17:36:05 by averdon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*create_long_min_char(void)
{
	char	*chr_number;
	char	*min_int;
	int		i;

	chr_number = ft_calloc(21, sizeof(char));
	if (!chr_number)
		return (NULL);
	min_int = "-9223372036854775808";
	i = 0;
	while (i < 20)
	{
		chr_number[i] = min_int[i];
		i++;
	}
	return (chr_number);
}

char	*create_long_char(long long div, int is_neg, long long n, int num_digit)
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

char	*ft_lltoa(long long n)
{
	long long	div;
	int			num_digit;
	int			is_neg;

	div = 1;
	num_digit = 1;
	is_neg = 0;
	if (n < 0)
	{
		if (n == LONG_MIN)
			return (create_long_min_char());
		num_digit++;
		n = n * -1;
		is_neg = 1;
	}
	while (n / 10 >= div)
	{
		div = div * 10;
		num_digit++;
	}
	return (create_long_char(div, is_neg, n, num_digit));
}

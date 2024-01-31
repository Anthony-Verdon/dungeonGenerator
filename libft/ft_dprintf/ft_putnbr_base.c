/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: averdon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 13:01:34 by averdon           #+#    #+#             */
/*   Updated: 2022/11/26 15:23:41 by averdon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"ft_dprintf.h"

static int	conditions(char *base)
{
	int	len_base;
	int	i;
	int	j;

	len_base = ft_strlen(base);
	i = 0;
	if (len_base == 0 || len_base == 1)
		return (0);
	while (base[i] != '\0')
	{
		if (base[i] == '+' || base[i] == '-')
			return (0);
		j = i + 1;
		while (base[j] != '\0')
		{
			if (base[i] == base[j])
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

void	ft_putnbr_hex(int fd, int nbr, char *base, int *n)
{
	int			len_base;
	long int	nbr_long;

	nbr_long = nbr;
	if (conditions(base) == 1)
	{
		len_base = ft_strlen(base);
		if (nbr_long < 0)
			nbr_long = ft_iterative_power(len_base, 8) + nbr_long;
		if (nbr_long / len_base != 0)
			ft_putnbr_hex(fd, nbr_long / len_base, base, n);
		write(fd, &base[nbr_long % len_base], 1);
		(*n)++;
	}
}

void	ft_putnbr_dec(int fd, int nbr, int *n)
{
	int			len_base;
	long int	nbr_long;
	char		*base;

	base = "0123456789";
	nbr_long = nbr;
	if (conditions(base) == 1)
	{
		len_base = ft_strlen(base);
		if (nbr_long < 0)
		{
			nbr_long = -nbr_long;
			write(1, "-", 1);
			(*n)++;
		}
		if (nbr_long / len_base != 0)
			ft_putnbr_dec (fd, nbr_long / len_base, n);
		write(fd, &base[nbr_long % len_base], 1);
		(*n)++;
	}
}

void	ft_check_pointer(int fd, unsigned long nbr, char *base, int *n)
{
	if ((void *)nbr == NULL)
	{
		write(fd, "(nil)", 5);
		(*n) = 5;
		return ;
	}
	else
	{
		write(fd, "0x", 2);
		(*n) = 2;
		ft_put_unbr(fd, nbr, base, n);
	}
}

void	ft_put_unbr(int fd, unsigned long nbr, char *base, int *n)
{
	int			len_base;

	if (conditions(base) == 1)
	{
		len_base = ft_strlen(base);
		if (nbr / len_base != 0)
			ft_put_unbr(fd, nbr / len_base, base, n);
		write(fd, &base[nbr % len_base], 1);
		(*n)++;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: averdon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 18:54:34 by averdon           #+#    #+#             */
/*   Updated: 2022/11/26 15:18:47 by averdon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"ft_dprintf.h"

static int	replace(int fd, int c, va_list args)
{
	int		num_char;
	char	*hexa;

	num_char = 0;
	hexa = "0123456789abcdef";
	if (c == 'c')
		num_char = ft_putchar_fd(va_arg(args, int), fd);
	else if (c == 's')
		num_char = ft_putstr_fd(va_arg(args, char *), fd);
	else if (c == 'p')
		ft_check_pointer(fd, va_arg(args, unsigned long), hexa, &num_char);
	else if (c == 'd' || c == 'i')
		ft_putnbr_dec(fd, va_arg(args, int), &num_char);
	else if (c == 'u')
		ft_put_unbr(fd, va_arg(args, unsigned int), "0123456789", &num_char);
	else if (c == 'x')
		ft_putnbr_hex(fd, va_arg(args, int), hexa, &num_char);
	else if (c == 'X')
		ft_putnbr_hex(fd, va_arg(args, int), "0123456789ABCDEF", &num_char);
	else if (c == '%')
		num_char = ft_putchar_fd('%', fd);
	return (num_char);
}

static int	check(int fd, char c, va_list args)
{
	int	len_write;

	len_write = 0;
	if (ft_strchr("cspdiuxX%", c))
		len_write += replace(fd, c, args);
	else
	{
		len_write += ft_putchar_fd('%', fd);
		len_write += ft_putchar_fd(c, fd);
	}
	return (len_write);
}

int	ft_dprintf(int fd, const char *str, ...)
{
	va_list	args;
	int		len;
	int		i;
	int		len_write;

	if (!str)
		return (-1);
	va_start(args, str);
	len = ft_strlen(str);
	i = 0;
	len_write = 0;
	while (i < len)
	{
		if (str[i] == '%')
		{
			i++;
			len_write += check(fd, str[i], args);
		}
		else
			len_write += ft_putchar_fd(str[i], fd);
		i++;
	}
	va_end(args);
	return (len_write);
}

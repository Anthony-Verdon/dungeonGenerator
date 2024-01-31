/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_multiple_arg.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlocusso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 09:37:57 by nlocusso          #+#    #+#             */
/*   Updated: 2022/12/08 18:01:21 by averdon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	in_str(char *str, char *charset, int i)
{
	int	cnt;

	cnt = 0;
	if (charset[cnt] == '\0')
		return (0);
	while (charset[cnt] != '\0')
	{
		if (str[i] == charset[cnt])
			return (1);
		cnt++;
	}
	return (0);
}

int	nb_word(char *str, char *charset)
{
	int	cnt;
	int	i;

	i = 0;
	cnt = 0;
	while (str[i] != '\0')
	{
		if (in_str(str, charset, i) == 1 && in_str(str, charset, i + 1) == 0)
			cnt++;
		i++;
	}
	cnt++;
	return (cnt);
}

int	length_malloc(char *str, char *charset)
{
	int	length;
	int	i;

	i = 0;
	length = 0;
	while (in_str(str, charset, i) == 0 && str[i] != '\0')
	{
		i++;
		length++;
	}
	return (length);
}

char	**ft_split_multiple_arg(char *str, char *charset)
{
	int		i;
	int		x;
	char	**tab;
	int		j;

	i = -1;
	x = 0;
	tab = ft_calloc((nb_word(str, charset) + 1), sizeof(char *));
	while (str[++i] != '\0')
	{
		j = 0;
		while (in_str(str, charset, i) == 1)
			i++;
		tab[x] = ft_calloc(length_malloc(str, charset) + 1, sizeof(char));
		while (in_str(str, charset, i) == 0 && str[i] != '\0')
		{
			tab[x][j] = str[i];
			j++;
			i++;
		}
		tab[x][j] = 0;
		x++;
	}
	tab[x] = NULL;
	return (tab);
}

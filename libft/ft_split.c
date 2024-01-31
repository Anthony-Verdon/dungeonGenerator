/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: averdon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 17:00:23 by averdon           #+#    #+#             */
/*   Updated: 2022/11/29 10:54:18 by nlocusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

int	count_word(char const *s, char c)
{
	int	i;
	int	num_word;

	i = 0;
	num_word = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			num_word++;
			while (s[i] != c && s[i])
				i++;
			i--;
		}
		i++;
	}
	return (num_word + 1);
}

char	**ft_split(char const *s, char c)
{
	int		i;
	int		j;
	char	**array;
	int		index;

	if (!s)
		return (NULL);
	array = ft_calloc(count_word(s, c), sizeof(char *));
	if (!array)
		return (NULL);
	i = -1;
	index = 0;
	while (s[++i])
	{
		if (s[i] != c)
		{
			j = 0;
			while (s[i + j] != c && s[i + j])
				j++;
			array[index++] = ft_substr(s, i, j);
			i += j - 1;
		}
	}
	array[index] = NULL;
	return (array);
}

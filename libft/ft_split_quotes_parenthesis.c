/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_quotes_parenthesis.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: averdon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 17:00:23 by averdon           #+#    #+#             */
/*   Updated: 2023/01/10 14:24:39 by averdon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

static int	count_word(char const *s, char c)
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

static int	substract_block(char *s, char c, char ***array, int *index)
{
	static int		single_opened;
	static int		double_opened;
	int				j;

	j = 0;
	while (s[j] && (s[j] != c || single_opened
			|| double_opened || !parenthesis_closed_split(&s[j])))
	{
		check_quotes(&single_opened, &double_opened, s[j]);
		j++;
	}
	(*array)[(*index)++] = ft_substr(s, 0, j);
	return (j - 1);
}

char	**ft_split_quotes_parenthesis(char *s, char c)
{
	int		i;
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
		if (s[i] != c && parenthesis_closed_split(&s[i]))
		{
			i += substract_block(&s[i], c, &array, &index);
		}
	}
	if (index == 0)
	{
		array[index] = ft_strdup(s);
		index++;
	}
	array[index] = NULL;
	return (array);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_quotes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: averdon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 17:00:23 by averdon           #+#    #+#             */
/*   Updated: 2023/01/10 15:04:42 by averdon          ###   ########.fr       */
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

void	check_quotes(int *single_opened, int *double_opened, char c)
{
	if (c == '\'')
	{
		if (!(*double_opened) && !(*single_opened))
			*single_opened = 1;
		else if (!(*double_opened) && *single_opened)
			*single_opened = 0;
	}
	if (c == '\"')
	{
		if (!(*single_opened) && !(*double_opened))
			*double_opened = 1;
		else if (!(*single_opened) && *double_opened)
			*double_opened = 0;
	}
}

static int	substract_block(char *s, char c, char ***array, int *index)
{
	int				j;
	static int		single_opened;
	static int		double_opened;

	j = 0;
	while (s[j] && (s[j] != c || single_opened || double_opened))
	{
		check_quotes(&single_opened, &double_opened, s[j]);
		j++;
	}
	(*array)[(*index)++] = ft_substr(s, 0, j);
	return (j - 1);
}

char	**ft_split_quotes(char *s, char c)
{
	int		i;
	char	**array;
	int		index;

	if (!s)
		return (NULL);
	array = ft_calloc(count_word(s, c) + 1, sizeof(char *));
	if (!array)
		return (NULL);
	i = -1;
	index = 0;
	while (s[++i])
	{
		if (s[i] != c)
			i += substract_block(&s[i], c, &array, &index);
	}
	if (index == 0)
	{
		array[index] = ft_strdup(s);
		index++;
	}
	array[index] = NULL;
	return (array);
}

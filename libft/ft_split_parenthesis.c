/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_parenthesis.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: averdon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 17:00:23 by averdon           #+#    #+#             */
/*   Updated: 2023/01/10 16:20:11 by averdon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

int	skip_quotes(char *command)
{
	int	i;

	i = 0;
	if (command[i] == '\'')
	{
		i++;
		while (command[i] && command[i] != '\'')
			i++;
	}
	else if (command[i] == '\"')
	{
		i++;
		while (command[i] && command[i] != '\"')
			i++;
	}
	return (i);
}

int	parenthesis_closed_split(char *command)
{
	int	i;
	int	parenthesis;

	i = 0;
	parenthesis = 0;
	while (command[i])
	{
		if (command[i] == '\'' || command[i] == '\"')
			i += skip_quotes(&command[i]);
		else if (command[i] == '(')
			parenthesis++;
		else if (command[i] == ')')
			parenthesis--;
		if (parenthesis < 0)
			return (0);
		i++;
	}
	if (parenthesis == 0)
		return (1);
	else
		return (0);
}

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
	int		j;

	j = 0;
	while ((s[j] != c
			|| !parenthesis_closed_split(&s[j])) && s[j])
		j++;
	(*array)[(*index)++] = ft_substr(s, 0, j);
	return (j - 1);
}

char	**ft_split_parenthesis(char *s, char c)
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
			i += substract_block(&s[i], c, &array, &index);
	}
	if (index == 0)
		array[index++] = ft_strdup(s);
	array[index] = NULL;
	return (array);
}

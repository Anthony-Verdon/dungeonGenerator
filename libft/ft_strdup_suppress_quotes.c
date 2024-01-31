/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup_suppress_quotes.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: averdon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 12:43:52 by averdon           #+#    #+#             */
/*   Updated: 2023/01/10 12:50:54 by averdon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	detect_single_quotes(int *single_quotes, int *double_quotes,
		int *nb_skip, char *letter)
{
	if (*double_quotes == 1)
		*letter = '\'';
	else
	{
		(*nb_skip)++;
		if (*single_quotes == 1)
			*single_quotes = 0;
		else if (*single_quotes == 0)
			*single_quotes = 1;
	}
}

void	detect_double_quotes(int *single_quotes, int *double_quotes,
		int *nb_skip, char *letter)
{
	if (*single_quotes == 1)
		*letter = '\"';
	else
	{
		(*nb_skip)++;
		if (*double_quotes == 1)
			*double_quotes = 0;
		else if (*double_quotes == 0)
			*double_quotes = 1;
	}
}

char	*ft_strdup_supress_quotes(const char *s)
{
	char	*duplicate_string;
	size_t	i;
	int		single_quotes;
	int		double_quotes;
	int		nb_skip;

	duplicate_string = ft_calloc(ft_strlen(s) + 1, sizeof(char));
	if (!duplicate_string)
		return (NULL);
	i = -1;
	nb_skip = 0;
	single_quotes = 0;
	double_quotes = 0;
	while (++i < ft_strlen(s) + 1)
	{
		if (s[i] == '\'')
			detect_single_quotes(&single_quotes, &double_quotes, &nb_skip,
				&duplicate_string[i - nb_skip]);
		else if (s[i] == '"')
			detect_double_quotes(&single_quotes, &double_quotes, &nb_skip,
				&duplicate_string[i - nb_skip]);
		else
			duplicate_string[i - nb_skip] = s[i];
	}
	return (duplicate_string);
}

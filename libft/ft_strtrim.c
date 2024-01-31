/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: averdon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 09:42:45 by averdon           #+#    #+#             */
/*   Updated: 2023/01/11 17:38:53 by averdon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

int	calculate_length_start(char const *s1, char const *set)
{
	int	i;
	int	j;
	int	memory;

	i = 0;
	while (s1[i])
	{
		j = 0;
		memory = 1;
		while (set[j])
		{
			if (s1[i] == set[j])
				memory = 0;
			j++;
		}
		if (memory == 1)
			break ;
		i++;
	}
	return (i);
}

int	calculate_length_end(char const *s1, char const *set, int len_s1)
{
	int	y;
	int	j;
	int	memory;

	y = 0;
	while (len_s1 - y > 0 && s1[len_s1 - 1 - y])
	{
		j = 0;
		memory = 1;
		while (set[j])
		{
			if (s1[len_s1 - 1 - y] == set[j])
				memory = 0;
			j++;
		}
		if (memory == 1)
			break ;
		y++;
	}
	return (y);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	int		y;
	int		len_s1;
	int		space;
	char	*new_s;

	if (!s1)
		return (NULL);
	len_s1 = ft_strlen(s1);
	i = calculate_length_start(s1, set);
	y = calculate_length_end(s1, set, len_s1);
	space = len_s1 - i - y;
	if (space < 0)
		space = 0;
	new_s = malloc(space + 1);
	if (!new_s)
		return (NULL);
	y = 0;
	while (y < space)
	{
		new_s[y] = s1[i + y];
		y++;
	}
	new_s[y] = '\0';
	return (new_s);
}

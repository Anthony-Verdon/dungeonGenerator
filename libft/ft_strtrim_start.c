/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim_start.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: averdon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 13:29:28 by averdon           #+#    #+#             */
/*   Updated: 2022/11/29 13:40:17 by averdon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim_start(char const *s1, char const *set)
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
	space = len_s1 - i;
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcut.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: averdon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 23:33:04 by averdon           #+#    #+#             */
/*   Updated: 2022/11/30 23:33:06 by averdon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcut(char *s, int c)
{
	int		i;
	int		y;
	char	*new_str;

	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			break ;
		i++;
	}
	new_str = ft_calloc(i + 1, sizeof(char));
	if (!new_str)
		return (NULL);
	y = 0;
	while (y < i)
	{
		new_str[y] = s[y];
		y++;
	}
	return (new_str);
}

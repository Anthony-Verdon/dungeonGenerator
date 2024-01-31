/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcut_end.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: averdon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 16:04:33 by averdon           #+#    #+#             */
/*   Updated: 2022/11/29 17:41:47 by averdon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcut_end(char *s, int c)
{
	int		i;
	int		y;
	char	*new_str;
	char	*part_to_cut;

	part_to_cut = ft_strrchr(s, c);
	i = ft_strlen(s) - ft_strlen(part_to_cut);
	new_str = ft_calloc(i + 2, sizeof(char));
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

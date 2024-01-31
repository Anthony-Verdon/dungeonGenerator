/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: averdon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 12:08:44 by averdon           #+#    #+#             */
/*   Updated: 2022/10/03 15:27:12 by averdon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*duplicate_string;
	int		i;
	int		size_s;

	size_s = ft_strlen(s) + 1;
	duplicate_string = malloc(size_s);
	if (!duplicate_string)
		return (NULL);
	i = 0;
	while (i < size_s)
	{
		duplicate_string[i] = s[i];
		i++;
	}
	return (duplicate_string);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: averdon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 17:52:05 by averdon           #+#    #+#             */
/*   Updated: 2022/10/03 13:40:27 by averdon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	j;
	size_t	y;

	i = 0;
	j = 0;
	if (!dst && size == 0)
		return (ft_strlen(src));
	while (dst[i] && i < size)
		i++;
	if (dst[i] || size == 0)
	{
		y = ft_strlen(src);
		return (y + size);
	}
	while (src[j] && i + j + 1 < size)
	{
		dst[i + j] = src[j];
		j++;
	}
	dst[i + j] = '\0';
	while (src[j])
		j++;
	return (i + j);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: averdon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 15:20:35 by averdon           #+#    #+#             */
/*   Updated: 2022/09/27 19:25:49 by averdon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	char	*to_return;

	i = 0;
	to_return = 0;
	while (s[i])
	{
		if (s[i] == (unsigned char)c)
			to_return = (char *)&s[i];
		i++;
	}
	if (s[i] == c)
		to_return = (char *)&s[i];
	return (to_return);
}

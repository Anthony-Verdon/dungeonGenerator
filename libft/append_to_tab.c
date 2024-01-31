/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   append_to_tab.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: averdon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 20:10:50 by averdon           #+#    #+#             */
/*   Updated: 2023/01/18 20:53:34 by averdon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_len_tab(char **tab)
{
	int	i;

	if (!tab)
		return (0);
	i = 0;
	while (tab[i])
		i++;
	return (i);
}

void	free_tab(char **tab)
{
	int	i;

	if (tab)
	{
		i = 0;
		while (tab[i])
		{
			free(tab[i]);
			i++;
		}
		free(tab);
	}
}

int	copy_tab(char **tab, char **new_tab)
{
	int		i;

	i = 0;
	while (tab[i])
	{
		new_tab[i] = ft_strdup(tab[i]);
		if (!new_tab[i])
			return (0);
		i++;
	}
	return (1);
}

char	**append_to_tab(char **tab, char *new_elt)
{
	int		last_index_tab;
	char	**new_tab;

	new_tab = ft_calloc(ft_len_tab(tab) + 2, sizeof(char *));
	if (!new_tab)
		return (NULL);
	if (tab)
	{
		if (!copy_tab(tab, new_tab))
		{
			free_tab(new_tab);
			return (NULL);
		}
	}
	last_index_tab = ft_len_tab(new_tab);
	new_tab[last_index_tab] = ft_strdup(new_elt);
	if (!new_tab[last_index_tab])
	{
		free_tab(new_tab);
		return (NULL);
	}
	free_tab(tab);
	return (new_tab);
}

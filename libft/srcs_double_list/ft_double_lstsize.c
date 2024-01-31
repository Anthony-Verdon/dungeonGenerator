/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_double_lstsize.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: averdon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 17:45:30 by averdon           #+#    #+#             */
/*   Updated: 2022/11/28 17:50:14 by averdon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_double_list.h"

int	ft_double_lstsize(t_double_list *list)
{
	int	i;

	i = 0;
	while (list)
	{
		list = list->next;
		i++;
	}
	return (i);
}

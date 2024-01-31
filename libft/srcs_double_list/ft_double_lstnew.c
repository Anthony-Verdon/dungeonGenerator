/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_double_lstnew.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: averdon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 09:38:09 by averdon           #+#    #+#             */
/*   Updated: 2022/10/19 18:45:05 by averdon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"ft_double_list.h"

t_double_list	*ft_double_lstnew(void *content)
{
	t_double_list	*new_element;

	new_element = malloc(sizeof(t_double_list));
	if (!new_element)
		return (NULL);
	new_element->content = content;
	new_element->next = NULL;
	new_element->prev = NULL;
	return (new_element);
}

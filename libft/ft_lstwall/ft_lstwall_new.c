/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: averdon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 09:38:09 by averdon           #+#    #+#             */
/*   Updated: 2022/10/03 12:44:31 by averdon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"
#include <stdio.h>

t_lstwall *ft_lstwall_new(int x, int y)
{
    t_lstwall *new_element;

    new_element = malloc(sizeof(t_lstwall));
    if (!new_element)
        return (NULL);
    printf("New Wall x:%i y:%i\n", x, y);
    new_element->x = x;
    new_element->y = y;
    new_element->selected = false;
    new_element->next = new_element;
    return (new_element);
}

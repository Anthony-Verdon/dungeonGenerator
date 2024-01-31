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

t_lstsector *ft_lstsec_new(int floorHeight, int ceilingHeight, t_lstwall *walls)
{
    t_lstsector *new_element;

    new_element = malloc(sizeof(t_lstsector));
    if (!new_element)
        return (NULL);
    new_element->ceilingHeight = ceilingHeight;
    new_element->floorHeight = floorHeight;
    new_element->walls = walls;
    new_element->close = false;
    new_element->selected = false;
    new_element->next = NULL;
    return (new_element);
}

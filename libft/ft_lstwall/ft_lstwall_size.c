/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: averdon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 12:45:52 by averdon           #+#    #+#             */
/*   Updated: 2022/10/03 12:49:18 by averdon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int ft_lstwall_size(t_lstwall *lst)
{
    if (!lst)
        return 0;

    int i = 0;
    t_lstwall *current = lst;
    do
    {
        current = current->next;
        i++;
    } while (current != NULL && current != lst);
    return i;
}
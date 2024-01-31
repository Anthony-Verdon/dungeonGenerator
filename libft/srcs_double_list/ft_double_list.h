/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_double_list.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: averdon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 18:39:50 by averdon           #+#    #+#             */
/*   Updated: 2022/11/28 17:46:48 by averdon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_DOUBLE_LIST_H

#include <stdlib.h>

typedef struct s_double_list
{
    void *content;
    struct s_double_list *prev;
    struct s_double_list *next;
} t_double_list;

void ft_double_lstadd_back(t_double_list **lst, t_double_list *node);
void ft_double_lstadd_front(t_double_list **lst, t_double_list *node);
void ft_double_lstclear(t_double_list **lst, void (*del)(void *));
void ft_double_lstdelone(t_double_list *lst, void (*del)(void *));
t_double_list *ft_double_lstlast(t_double_list *lst);
t_double_list *ft_double_lstnew(void *content);
int ft_double_lstsize(t_double_list *list);

#endif

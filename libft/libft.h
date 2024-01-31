/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: averdon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 11:28:31 by averdon           #+#    #+#             */
/*   Updated: 2023/01/26 10:58:51 by averdon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
#define LIBFT_H

#include "ft_dprintf/ft_dprintf.h"
#include "gnl/get_next_line.h"
#include "srcs_double_list/ft_double_list.h"
#include <limits.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct s_list
{
    void *content;
    struct s_list *next;
} t_list;

typedef struct s_lstwall
{
    int x, y;
    bool selected;
    // texture
    struct s_lstwall *next;
} t_lstwall;

typedef struct s_lstsector
{
    bool close;
    bool selected;
    int floorHeight;
    int ceilingHeight;
    struct s_lstwall *walls;
    struct s_lstsector *next;
} t_lstsector;

int ft_len_tab(char **tab);
int check_extension(char *str, char *extension);
void ft_free_array(char **str);
char **ft_split_multiple_arg(char *str, char *charset);
int ft_strcmp(char *s1, char *s2);
char *ft_strcut(char *s, int c);
char *ft_strcut_end(char *s, int c);
char *ft_strtrim_start(char const *s1, char const *set);
int calculate_length_start(char const *s1, char const *set);
char **ft_split_quotes(char *s, char c);
char **ft_split_quotes_trim(char *s, char c);
int overflow(int number);
long long ft_atoll(const char *nptr);
char *ft_lltoa(long long n);
char **ft_split_parenthesis(char *s, char c);
int parenthesis_closed_split(char *command);
void check_quotes(int *single_opened, int *double_opened, char c);
char **ft_split_quotes_parenthesis(char *s, char c);

int ft_isalpha(int c);
int ft_isdigit(int c);
int ft_isalnum(int c);
int ft_isascii(int c);
int ft_isprint(int c);
size_t ft_strlen(const char *s);
void *ft_memset(void *s, int c, size_t n);
void ft_bzero(void *s, size_t n);
void *ft_memcpy(void *dest, const void *src, size_t n);
void *ft_memmove(void *dest, const void *src, size_t n);
size_t ft_strlcpy(char *dst, const char *src, size_t size);
size_t ft_strlcat(char *dst, const char *src, size_t size);
int ft_toupper(int c);
int ft_tolower(int c);
char *ft_strchr(const char *s, int c);
char *ft_strrchr(const char *s, int c);
int ft_strncmp(const char *s1, const char *s2, size_t n);
void *ft_memchr(const void *s, int c, size_t n);
int ft_memcmp(const void *s1, const void *s2, size_t n);
char *ft_strnstr(const char *big, const char *little, size_t len);
int ft_atoi(const char *nptr);
int ft_atoi_base(const char *str, const char *base);
void *ft_calloc(size_t nmemb, size_t size);
char *ft_strdup(const char *s);

char *ft_substr(char const *s, unsigned int start, size_t len);
char *ft_strjoin(char const *s1, char const *s2);
char *ft_strtrim(char const *s1, char const *set);
char **ft_split(char const *s, char c);
char *ft_itoa(int n);
char *ft_strmapi(char const *s, char (*f)(unsigned int, char));
void ft_striteri(char *s, void (*f)(unsigned int, char *));
int ft_putchar_fd(char c, int fd);
int ft_putstr_fd(char *s, int fd);
void ft_putendl_fd(char *s, int fd);
void ft_putnbr_fd(int n, int fd);

t_list *ft_lstnew(void *content);
void ft_lstadd_front(t_list **lst, t_list *new_l);
int ft_lstsize(t_list *lst);
t_list *ft_lstlast(t_list *lst);
void ft_lstadd_back(t_list **lst, t_list *new_l);
void ft_lstdelone(t_list *lst, void (*del)(void *));
void ft_lstclear(t_list **lst, void (*del)(void *));
void ft_lstiter(t_list *lst, void (*f)(void *));
t_list *ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));
char *ft_strdup_supress_quotes(const char *s);
int skip_quotes(char *command);
char **append_to_tab(char **tab, char *new_elt);
void free_tab(char **tab);

t_lstwall *ft_lstwall_new(int gridX, int gridY);
void ft_lstwall_add_front(t_lstwall **lst, t_lstwall *new_l);
int ft_lstwall_size(t_lstwall *lst);
t_lstwall *ft_lstwall_last(t_lstwall *lst);
void ft_lstwall_add_back(t_lstwall **lst, t_lstwall *new_l);
void ft_lstwall_delone(t_lstwall *lst, void (*del)(void *));
void ft_lstwall_clear(t_lstwall **lst, void (*del)(void *));
void ft_lstwall_iter(t_lstwall *lst, void (*f)(void *));

t_lstsector *ft_lstsec_new(int floorHeight, int ceilingHeight, t_lstwall *walls);
void ft_lstsec_add_front(t_lstsector **lst, t_lstsector *new_l);
int ft_lstsec_size(t_lstsector *lst);
t_lstsector *ft_lstsec_last(t_lstsector *lst);
void ft_lstsec_add_back(t_lstsector **lst, t_lstsector *new_l);
void ft_lstsec_delone(t_lstsector *lst, void (*del)(void *));
void ft_lstsec_clear(t_lstsector **lst, void (*del)(void *));
void ft_lstsec_iter(t_lstsector *lst, void (*f)(void *));
#endif

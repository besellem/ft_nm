/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besellem <besellem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 13:26:20 by besellem          #+#    #+#             */
/*   Updated: 2022/04/08 01:54:19 by besellem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LIST_H
# define FT_LIST_H

# include <stdlib.h>

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

t_list	*ft_lstnew(void *content);
void	ft_lstadd_front(t_list **alst, t_list *new);
void	ft_lstadd_back(t_list **alst, t_list *new);
t_list	*ft_lst_push_front(t_list **head, void *content);
t_list	*ft_lst_push_back(t_list **head, void *content);
void	ft_lst_push_sorted(t_list **begin_list, void *data, int (*cmp)());

void	ft_lst_merge(t_list **begin_list1, t_list *begin_list2);

void	ft_lst_sort(t_list **lst, int (*cmp)());
void	ft_lst_qsort(t_list **head, int (*cmp)());

void	ft_lstdelone(t_list *lst, void (*del)(void *));
void	ft_lstclear(t_list **lst, void (*del)(void *));

char	**ft_lst2strs(t_list *lst);
void	ft_lstiter(t_list *lst, void (*f)(void *));
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));

int		ft_lstsize(t_list *lst);
t_list	*ft_lstlast(t_list *lst);
t_list	*ft_lst_at(t_list *lst, size_t index);
t_list	*ft_lst_find(t_list *lst, void *ref, int (*cmp)());

void	ft_lst_print(t_list *lst, void (*f)());

#endif

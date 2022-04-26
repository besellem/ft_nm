/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_push_sorted.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besellem <besellem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 16:59:26 by besellem          #+#    #+#             */
/*   Updated: 2022/04/13 12:01:27 by besellem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_list.h"

/*
** add a new element in a sorted list.
** the api user must check if the list is sorted.
** if `data' is NULL, we do nothing
*/

void	ft_lst_push_sorted(t_list **begin_list, void *data, int (*cmp)())
{
	t_list	*lst;
	t_list	*next;
	t_list	*prev;

	if (!begin_list || !data || !(*cmp))
		return ;
	lst = *begin_list;
	prev = NULL;
	while (lst && (*cmp)(lst->content, data) <= 0)
	{
		prev = lst;
		lst = lst->next;
	}
	if (!lst)
		ft_lst_push_back(begin_list, data);
	else if (!prev)
		ft_lst_push_front(begin_list, data);
	else
	{
		next = prev->next;
		prev->next = ft_lstnew(data);
		prev->next->next = next;
	}
}

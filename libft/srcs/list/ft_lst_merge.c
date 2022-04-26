/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_merge.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besellem <besellem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 16:58:52 by besellem          #+#    #+#             */
/*   Updated: 2022/03/31 16:59:14 by besellem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_list.h"

/*
** merge two lists
** the pointers are not deeply copied
** warning: do not free the second list. you may set begin_list2 to NULL to
**          avoid any conflicts.
*/
void	ft_lst_merge(t_list **begin_list1, t_list *begin_list2)
{
	t_list	*last;

	if (!begin_list1 || !begin_list2 || *begin_list1 == begin_list2)
		return ;
	last = ft_lstlast(*begin_list1);
	if (last)
		last->next = begin_list2;
	else
		*begin_list1 = begin_list2;
}

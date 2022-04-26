/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_find.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besellem <besellem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 22:27:57 by besellem          #+#    #+#             */
/*   Updated: 2022/03/28 22:30:05 by besellem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_list.h"

t_list	*ft_lst_find(t_list *lst, void *ref, int (*cmp)())
{
	while (lst)
	{
		if (0 == (*cmp)(lst->content, ref))
			return (lst);
		lst = lst->next;
	}
	return (NULL);
}

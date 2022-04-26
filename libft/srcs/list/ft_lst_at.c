/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_at.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besellem <besellem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/29 17:35:08 by besellem          #+#    #+#             */
/*   Updated: 2022/03/28 22:14:43 by besellem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_list.h"

/*
** Return the nth node of a list
*/
t_list	*ft_lst_at(t_list *lst, size_t index)
{
	size_t	i;

	i = 0;
	while (lst)
	{
		if (i++ == index)
			return (lst);
		lst = lst->next;
	}
	return (NULL);
}

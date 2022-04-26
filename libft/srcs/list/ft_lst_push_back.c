/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_push_back.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besellem <besellem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 22:06:55 by besellem          #+#    #+#             */
/*   Updated: 2022/03/28 22:35:25 by besellem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_list.h"

t_list	*ft_lst_push_back(t_list **head, void *content)
{
	t_list	*_p;

	if (!head)
		return (NULL);
	_p = ft_lstnew(content);
	if (!_p)
		return (NULL);
	ft_lstadd_back(head, _p);
	return (_p);
}

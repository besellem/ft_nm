/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   htabl_destroy.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besellem <besellem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/01 22:16:35 by besellem          #+#    #+#             */
/*   Updated: 2022/05/01 23:35:04 by besellem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "htabl.h"
#include "ft_string.h"

void	htabl_destroy(t_htabl **ht)
{
	t_htabl_lst	**nodes;
	t_htabl_lst	*lst;
	size_t		i;

	if (!*ht)
		return ;
	nodes = (*ht)->_root;
	if (nodes)
	{
		i = 0;
		while (i < (*ht)->_size)
		{
			lst = nodes[i];
			while ((*ht)->_del_node && lst)
			{
				(*ht)->_del_node(lst->content);
				lst = lst->next;
			}
			lst_clear(&nodes[i], free);
			++i;
		}
	}
	ft_memdel((void **)&(*ht)->_root);
	ft_memdel((void **)&(*ht));
}

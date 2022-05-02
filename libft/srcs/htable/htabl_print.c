/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   htabl_print.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besellem <besellem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/01 22:20:59 by besellem          #+#    #+#             */
/*   Updated: 2022/05/01 23:50:34 by besellem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "htabl.h"
#include "ft_stdio.h"

static void	_htabl_print_lst(t_htabl_lst *lst, void (*print_val)(void *))
{
	while (lst)
	{
		if (lst->content)
		{
			if ((*print_val))
			{
				ft_printf("\t[" B_CYAN "key" CLR_COLOR ": '%s', "
					B_CYAN "val" CLR_COLOR ": ",
					lst->content->key);
				(*print_val)(lst->content->value);
				ft_putstr("]");
			}
			else
			{	
				ft_printf("\t[" B_CYAN "ptr" CLR_COLOR ": %11p, "
					B_CYAN "key" CLR_COLOR ": '%s']",
					lst->content->value, lst->content->key);
			}
			if (lst->next)
				ft_putstr(",");
			ft_putstr("\n");
		}
		lst = lst->next;
	}
}

void	htabl_print(const t_htabl *ht, void (*print_val)())
{
	t_htabl_lst		**nodes;
	size_t			i;
	bool			newline;

	nodes = ht->_root;
	i = 0;
	while (i < ht->_size)
	{
		newline = (nodes[i] && nodes[i]->content);
		if (newline)
			ft_printf("[" B_YELLOW "#%4zu" CLR_COLOR "] {\n", i);
		_htabl_print_lst(nodes[i], print_val);
		if (newline)
			ft_putstr("}\n");
		++i;
	}
}

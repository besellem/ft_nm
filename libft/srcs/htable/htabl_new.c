/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   htabl_new.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besellem <besellem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/01 23:28:56 by besellem          #+#    #+#             */
/*   Updated: 2022/05/01 23:35:47 by besellem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "htabl.h"
#include "ft_stdlib.h"
#include "ft_string.h"

#define HTABL_DEFAULT_SIZE  4096

t_htabl	*htabl_new(void (*del_node)(t_htabl_node *))
{
	t_htabl	*ht;

	ht = ft_calloc(1, sizeof(*ht));
	if (!ht)
		return (NULL);
	ht->_size = HTABL_DEFAULT_SIZE;
	ht->_del_node = del_node;
	ht->_root = ft_calloc(1, HTABL_DEFAULT_SIZE * sizeof(t_htabl_lst *));
	if (!ht->_root)
	{
		ft_memdel((void **)&ht);
		return (NULL);
	}
	return (ht);
}

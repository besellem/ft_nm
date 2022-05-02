/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   htabl_search.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besellem <besellem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/01 22:17:50 by besellem          #+#    #+#             */
/*   Updated: 2022/05/01 22:26:46 by besellem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "htabl.h"
#include "ft_string.h"

void	*htabl_search(const t_htabl *ht, const char *key)
{
	const size_t		idx = htabl_hash(key) % ht->_size;
	const t_htabl_lst	*lst = ht->_root[idx];

	while (lst)
	{
		if (lst->content && lst->content->key
			&& 0 == ft_strcmp(lst->content->key, key))
			return (lst->content->value);
		lst = lst->next;
	}
	return (NULL);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst2strs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besellem <besellem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/29 17:37:01 by besellem          #+#    #+#             */
/*   Updated: 2022/03/28 22:23:20 by besellem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_list.h"
#include "ft_stdlib.h"
#include "ft_string.h"

/*
** Convert a list to a `char **'
*/
char	**ft_lst2strs(t_list *lst)
{
	char	**strs;
	size_t	str_size;
	size_t	i;

	if (!lst)
		return (NULL);
	strs = (char **)malloc(sizeof(char *) * (ft_lstsize(lst) + 1));
	if (!strs)
		return (NULL);
	i = 0;
	while (lst)
	{
		str_size = ft_strlen((char *)lst->content);
		strs[i] = (char *)malloc(str_size + 1);
		strs[i][str_size] = 0;
		if (!strs[i])
			return (ft_strsfree(i, strs));
		ft_memcpy(strs[i], (char *)lst->content, str_size);
		lst = lst->next;
		++i;
	}
	strs[i] = NULL;
	return (strs);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sorting.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besellem <besellem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 21:29:05 by besellem          #+#    #+#             */
/*   Updated: 2022/05/03 10:31:30 by besellem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

int		sort_alpha_asc(t_symbol a, t_symbol b)
{
	char	*s1 = ft_strdup(a.name);
	char	*s2 = ft_strdup(b.name);
	char	*p1 = s1;
	char	*p2 = s2;
	int		res;

	ft_strclean(s1, "_");
	ft_strclean(s2, "_");
	ft_strlowcase(s1);
	ft_strlowcase(s2);
	
	res = ft_strcmp(s1, s2);
	if (0 == res)
		res = ft_strcmp(a.name, b.name);

	free(p1);
	free(p2);

	return res;
}

int		sort_alpha_desc(t_symbol a, t_symbol b)
{
	return sort_alpha_asc(b, a);
}

int		sort_addr_asc(t_symbol a, t_symbol b)
{
	// if (!ft_strncmp(a.name, "__asan_", 7) && a.offset > 0)
	// 	ft_printf("[%30s] off[%zu]\n", a.name, a.offset);
	
	// if (0 == (a.offset - b.offset) && (a.type == 'U' && b.type == 'U'))
	// 	return ft_strcmp(a.name, b.name);
	if (0 == (a.offset - b.offset))
	{
		// LOG
		return sort_alpha_asc(a, b);
	}
	return (int)(a.offset - b.offset);
}

int		sort_addr_desc(t_symbol a, t_symbol b)
{
	return sort_addr_asc(b, a);
}

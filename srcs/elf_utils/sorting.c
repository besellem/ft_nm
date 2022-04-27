/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sorting.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besellem <besellem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 21:29:05 by besellem          #+#    #+#             */
/*   Updated: 2022/04/26 21:40:13 by besellem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

int		sort_alpha_asc(t_symbol a, t_symbol b)
{
	char	*p1 = a.name;
	char	*p2 = b.name;
	char	*s1;
	char	*s2;
	int		res;

	for ( ; *p1 && '_' == *p1; ++p1);
	for ( ; *p2 && '_' == *p2; ++p2);

	s1 = ft_strdup(p1);
	s2 = ft_strdup(p2);
	ft_strlowcase(s1);
	ft_strlowcase(s2);
	
	res = ft_strcmp(s1, s2);

	free(s1);
	free(s2);
	return res;
}

int		sort_alpha_desc(t_symbol a, t_symbol b)
{
	return sort_alpha_asc(b, a);
}

int		sort_addr_asc(t_symbol a, t_symbol b)
{
	return (int)(a.offset - b.offset);
}

int		sort_addr_desc(t_symbol a, t_symbol b)
{
	return sort_addr_asc(b, a);
}

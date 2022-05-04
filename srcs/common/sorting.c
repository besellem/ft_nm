/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sorting.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besellem <besellem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 21:29:05 by besellem          #+#    #+#             */
/*   Updated: 2022/05/04 22:48:25 by besellem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

int		sort_alpha_asc(t_symbol a, t_symbol b)
{
	char	*s1 = ft_strdup(a.name);
	char	*s2 = ft_strdup(b.name);
	void	*p1 = s1;
	void	*p2 = s2;
	int		res;

	ft_strclean(s1, "_/@."); // TODO: check if '.' is correct
	ft_strclean(s2, "_/@."); // TODO: check if '.' is correct
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
	// -n option
	if ('t' == ft_tolower(a.type) && 'u' == ft_tolower(b.type))
		return 1;

	if (0 == (a.offset - b.offset))
		return sort_alpha_asc(a, b);

	return (int)(a.offset - b.offset);
}

int		sort_addr_desc(t_symbol a, t_symbol b)
{
	return sort_addr_asc(b, a);
}

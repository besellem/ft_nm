/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besellem <besellem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/13 02:29:31 by besellem          #+#    #+#             */
/*   Updated: 2021/11/07 14:17:26 by besellem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"
#include "defs.h"

char	*ft_strchr(const char *s, int c)
{
	if (c == 0)
		return ((char *)(s + ft_strlen(s)));
	while (*s)
	{
		if (*s++ == (char)c)
			return ((char *)--s);
	}
	return (NULL);
}

/* optimized code - does not pass a tester */
// char	*ft_strchr(const char *s, int c)
// {
// 	const size_t	*l_str = (const size_t *)s;
// 	char			*c_str;
// 	size_t			_haszero;
// 	size_t			_hasvalue;

// 	if (c == 0)
// 		return ((char *)(s + ft_strlen(s)));
// 	while (TRUE)
// 	{
// 		_haszero = ((*l_str) - LOWS) & ~(*l_str) & HIGHS;
// 		_hasvalue = (*l_str) ^ (LOWS * ((char)c));
// 		_hasvalue = ((_hasvalue) - LOWS) & ~(_hasvalue) & HIGHS;
// 		if (_haszero || _hasvalue)
// 			break ;
// 		++l_str;
// 	}
// 	c_str = (char *)l_str;
// 	while (*c_str)
// 	{
// 		if (*c_str++ == (char)c)
// 			return ((char *)--c_str);
// 	}
// 	return (NULL);
// }

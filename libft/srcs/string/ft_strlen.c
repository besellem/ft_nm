/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besellem <besellem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/13 02:29:36 by besellem          #+#    #+#             */
/*   Updated: 2021/11/07 14:20:46 by besellem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"
#include "defs.h"

/*
** 1GB in ~280 ms (the real one does it in ~100 ms)
**
** Uses a bit tricks found here:
** https://graphics.stanford.edu/~seander/bithacks.html#ZeroInWord
*/
size_t	ft_strlen(const char *s)
{
	size_t	*l_str;
	char	*c_str;

	if (LIBC_NO_CRASH_ON_NULL && !s)
		return (0);
	c_str = (char *)s;
	while ((uintptr_t)c_str % sizeof(size_t))
	{
		if (!*c_str)
			return (c_str - s);
		++c_str;
	}
	l_str = (size_t *)c_str;
	while (!(((*l_str) - LOWS) & ~(*l_str) & HIGHS))
		++l_str;
	c_str = (char *)l_str;
	while (*c_str)
		++c_str;
	return ((size_t)c_str - (size_t)s);
}

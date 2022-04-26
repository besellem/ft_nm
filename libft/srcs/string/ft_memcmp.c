/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besellem <besellem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/13 02:29:17 by besellem          #+#    #+#             */
/*   Updated: 2021/11/06 23:43:18 by besellem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"
#include "ft_stdint.h"
#include "defs.h"

__INLINE static int	__get_diff__(const t_uwide_int *p1, const t_uwide_int *p2)
{
	const unsigned char	*s1 = (const unsigned char *)p1;
	const unsigned char	*s2 = (const unsigned char *)p2;

	while (*s1++ == *s2++)
		;
	return (*--s1 - *--s2);
}

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const t_uwide_int	*p1 = (const t_uwide_int *)s1;
	const t_uwide_int	*p2 = (const t_uwide_int *)s2;
	unsigned char		*c1;
	unsigned char		*c2;

	if (n != 0)
	{
		while (n >= sizeof(t_uwide_int))
		{
			if (*p1++ != *p2++)
				return (__get_diff__(p1 - 1, p2 - 1));
			n -= sizeof(t_uwide_int);
		}
		c1 = (unsigned char *)p1;
		c2 = (unsigned char *)p2;
		while (n-- > 0)
		{
			if (*c1++ != *c2++)
				return ((int)(*--c1 - *--c2));
		}
	}
	return (0);
}

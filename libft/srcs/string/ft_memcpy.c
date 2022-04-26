/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besellem <besellem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/13 02:29:21 by besellem          #+#    #+#             */
/*   Updated: 2021/11/06 23:09:35 by besellem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"
#include "ft_stdint.h"
#include "defs.h"

/*
** Copy n bytes from src to dst.
**
** We first copy 8 or 16 bytes at a time using the wider integer type.
** At the end, we copy the remaining bytes using the char type.
*/
void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	t_uwide_int		*l_src;
	t_uwide_int		*l_dst;
	unsigned char	*c_src;
	unsigned char	*c_dst;

	if (dst == src)
		return (dst);
	l_src = (t_uwide_int *)src;
	l_dst = (t_uwide_int *)dst;
	while (n >= sizeof(t_uwide_int))
	{
		*l_dst++ = *l_src++;
		n -= sizeof(t_uwide_int);
	}
	if (n > 0)
	{
		c_src = (unsigned char *)l_src;
		c_dst = (unsigned char *)l_dst;
		while (n--)
			*c_dst++ = *c_src++;
	}
	return (dst);
}

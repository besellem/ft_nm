/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besellem <besellem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/13 02:29:26 by besellem          #+#    #+#             */
/*   Updated: 2021/11/06 23:11:55 by besellem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"
#include "defs.h"

__INLINE static t_uwide_int	__get_aligned_char__(unsigned char _c)
{
	t_uwide_int	c;

	if (0 == _c)
		return (0);
	c = _c;
	c = (c << 8) | c;
	c = (c << 16) | c;
	if (sizeof(t_uwide_int) > 4)
		c = (c << 32) | c;
	if (sizeof(t_uwide_int) > 8)
		c = (c << 64) | c;
	return (c);
}

void	*ft_memset(void *b, int c, size_t len)
{
	const t_uwide_int	val_aligned = __get_aligned_char__(c);
	t_uwide_int			*l_ptr;
	unsigned char		*c_ptr;

	c = (unsigned char)c;
	l_ptr = (t_uwide_int *)b;
	while (len >= sizeof(t_uwide_int))
	{
		*l_ptr++ = val_aligned;
		len -= sizeof(t_uwide_int);
	}
	if (len > 0)
	{
		c_ptr = (unsigned char *)l_ptr;
		while (len--)
			*c_ptr++ = c;
	}
	return (b);
}

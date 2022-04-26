/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besellem <besellem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/13 18:13:58 by besellem          #+#    #+#             */
/*   Updated: 2021/11/07 14:51:28 by besellem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"

char	*ft_strncpy(char *dst, const char *src, size_t len)
{
	const size_t	n = ft_strnlen(src, len);

	if (n < len)
		ft_bzero(dst + n, len - n);
	return ((char *)ft_memcpy(dst, src, n));
}

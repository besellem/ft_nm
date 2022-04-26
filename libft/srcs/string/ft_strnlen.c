/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnlen.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besellem <besellem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/13 12:40:58 by besellem          #+#    #+#             */
/*   Updated: 2021/11/07 14:33:32 by besellem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"
#include "defs.h"

size_t	ft_strnlen(const char *s, size_t maxlen)
{
	const size_t	size = ft_strlen(s);

	if ((LIBC_NO_CRASH_ON_NULL && !s) || maxlen == 0)
		return (0);
	if (size > maxlen)
		return (maxlen);
	else
		return (size);
}

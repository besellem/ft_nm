/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besellem <besellem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/13 02:29:00 by besellem          #+#    #+#             */
/*   Updated: 2022/04/08 14:31:14 by besellem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_stdlib.h"
#include "ft_string.h"

void	*ft_calloc(size_t count, size_t size)
{
	const size_t	_sz = count * size;
	void			*s;

	s = (void *)malloc(_sz);
	if (!s)
		return (NULL);
	ft_memset(s, 0, _sz);
	return (s);
}

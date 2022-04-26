/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_epur_str.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besellem <besellem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 03:28:31 by besellem          #+#    #+#             */
/*   Updated: 2021/12/02 11:50:47 by besellem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"
#include "ft_ctype.h"

/*
** Remove all the spaces in a string.
*/
static size_t	_size_epur_str_(const char *src)
{
	size_t	size;

	size = 0;
	while (*src)
	{
		if (ft_isspace(*src))
		{
			while (*src && ft_isspace(*(src + 1)))
				++src;
			if (*(src + 1))
				++size;
		}
		else
			++size;
		++src;
	}
	return (size);
}

static void	_epur_str_(char *dst, const char *src)
{
	size_t	i;

	i = 0;
	while (*src)
	{
		if (ft_isspace(*src))
		{
			while (*src && ft_isspace(*(src + 1)))
				++src;
			if (*(src + 1))
				dst[i++] = ' ';
		}
		else
			dst[i++] = *src;
		++src;
	}
	dst[i] = '\0';
}

char	*ft_epur_str(const char *str)
{
	char	*new;
	size_t	size;

	if (!str)
		return (NULL);
	while (*str && ft_isspace(*str))
		++str;
	size = _size_epur_str_(str);
	new = (char *)malloc(size + 1);
	if (!new)
		return (NULL);
	_epur_str_(new, str);
	return (new);
}

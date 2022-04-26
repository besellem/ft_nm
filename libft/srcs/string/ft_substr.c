/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besellem <besellem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/13 21:49:02 by besellem          #+#    #+#             */
/*   Updated: 2021/05/09 21:35:08 by besellem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*new;
	size_t	size;
	size_t	new_size;

	if (!s)
		return (NULL);
	size = ft_strlen(s);
	if (size < start)
		return (ft_strdup(""));
	new_size = size - start;
	if (new_size > len)
		new_size = len;
	new = (char *)malloc(new_size + 1);
	if (!new)
		return (NULL);
	new[new_size] = '\0';
	return ((char *)ft_memcpy(new, s + start, new_size));
}

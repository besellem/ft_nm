/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   htabl_hash.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besellem <besellem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/01 22:22:57 by besellem          #+#    #+#             */
/*   Updated: 2022/05/01 22:26:19 by besellem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "htabl.h"

/*
** sdbm algorithm
** http://www.cse.yorku.ca/~oz/hash.html
*/
size_t	htabl_hash(const char *key)
{
	size_t	hash;
	int		c;

	hash = 0;
	while (*key)
	{
		c = (unsigned char)*key++;
		hash = c + (hash << 6) + (hash << 16) - hash;
	}
	return (hash);
}

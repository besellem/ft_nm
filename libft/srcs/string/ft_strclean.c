/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strclean.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besellem <besellem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/29 18:08:49 by besellem          #+#    #+#             */
/*   Updated: 2021/06/29 18:14:28 by besellem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"

/*
** Clean `charset' characters found in `s' by modifying the latter.
**
** ex:
** char	s[] = ";hello >yo<u";
** ft_strclean(s, ";<>");
**   => s == "hello you"
*/
char	*ft_strclean(char *s, const char *charset)
{
	return (ft_strnclean(s, charset, ft_strlen(s)));
}

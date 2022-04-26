/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnstr_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besellem <besellem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/18 10:28:35 by besellem          #+#    #+#             */
/*   Updated: 2021/10/29 00:59:49 by besellem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnstr_fd(char *s, int fd, size_t n)
{
	const size_t	len = ft_strlen(s);

	if (s)
	{
		if (n > len)
			n = len;
		write(fd, s, n);
	}
}

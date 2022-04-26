/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putaddr_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besellem <besellem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/29 17:31:03 by besellem          #+#    #+#             */
/*   Updated: 2021/10/29 01:09:08 by besellem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#define HEXA "0123456789abcdef"

void	ft_putaddr_fd(void *addr, int fd)
{
	unsigned long	ad;
	unsigned long	div;

	ad = (unsigned long)addr;
	div = 16;
	write(fd, "0x", 2);
	while (ad / div >= 16)
		div *= 16;
	while (div > 0)
	{
		write(fd, &HEXA[ad / div], 1);
		ad %= div;
		div /= 16;
	}
}

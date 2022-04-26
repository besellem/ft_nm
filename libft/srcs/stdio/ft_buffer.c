/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_buffer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besellem <besellem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/13 00:54:06 by besellem          #+#    #+#             */
/*   Updated: 2022/04/12 10:52:59 by besellem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_stdio.h"
#include "ft_string.h"
#include "ft_stdlib.h"
#include "defs.h"

t_buffer	*ft_init_buff(const t_buffer_attr *attr)
{
	static t_buffer	*buffer = NULL;

	if (buffer && attr && (attr->oflag & BUF_INIT))
	{
		free(buffer->__buff);
		free(buffer);
		buffer = NULL;
	}
	else if (!buffer)
	{
		buffer = (t_buffer *)ft_calloc(1, sizeof(t_buffer));
		if (!buffer)
			return (NULL);
		buffer->__buff = (char *)ft_calloc(1, __BUFF_SIZE__);
		if (attr)
			buffer->__fd = attr->fd;
		else
			buffer->__fd = STDOUT_FILENO;
	}
	return (buffer);
}

void	ft_destroy_buff(void)
{
	const t_buffer_attr	attr = {.fd = SYSCALL_ERR, .oflag = BUF_INIT};

	ft_init_buff(&attr);
}

int	ft_buffaddc(char c)
{
	t_buffer	*buffer;

	buffer = ft_init_buff(NULL);
	if (!buffer)
		return (SYSCALL_ERR);
	buffer->__buff[buffer->__index++] = c;
	if (__BUFF_SIZE__ == buffer->__index)
	{
		if (SYSCALL_ERR == write(buffer->__fd, buffer->__buff, __BUFF_SIZE__))
			return (SYSCALL_ERR);
		buffer->__index = 0;
		ft_bzero(buffer->__buff, __BUFF_SIZE__);
	}
	return (0);
}

int	ft_buffadd(const char *s)
{
	const size_t	size = ft_strlen(s);
	t_buffer		*buffer;

	if (!s)
		return (SYSCALL_ERR);
	buffer = ft_init_buff(NULL);
	if (!buffer)
		return (SYSCALL_ERR);
	if (size < (__BUFF_SIZE__ - buffer->__index))
	{
		ft_memcpy(buffer->__buff + buffer->__index, s, size);
		buffer->__index += size;
	}
	else
	{
		if (SYSCALL_ERR == write(buffer->__fd, buffer->__buff, buffer->__index))
			return (SYSCALL_ERR);
		if (SYSCALL_ERR == write(buffer->__fd, s, size))
			return (SYSCALL_ERR);
		buffer->__index = 0;
		ft_bzero(buffer->__buff, __BUFF_SIZE__);
	}
	return (0);
}

int	ft_flush_buff(void)
{
	const t_buffer	*buffer = ft_init_buff(NULL);

	if (!buffer)
		return (SYSCALL_ERR);
	if (buffer->__index > 0)
	{
		if (SYSCALL_ERR == write(buffer->__fd, buffer->__buff, buffer->__index))
			return (SYSCALL_ERR);
	}
	ft_destroy_buff();
	return (0);
}

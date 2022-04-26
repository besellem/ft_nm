/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besellem <besellem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 00:14:36 by besellem          #+#    #+#             */
/*   Updated: 2021/10/29 01:18:29 by besellem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "get_next_line.h"

static char	*ft_realloc_str(char *str, char **line, int *check)
{
	char			*new;
	unsigned int	i;

	new = NULL;
	if (str)
	{
		i = 0;
		while (str[i] && str[i] != '\n')
			++i;
		if (str[i] == '\n')
		{
			*check = GNL_OK;
			new = ft_strdup(str + i + 1);
		}
		else if (str[i])
			new = ft_strdup(str + i);
		*line = ft_strndup(str, i);
		ft_memdel((void **)&str);
	}
	return (new);
}

static char	*ft_read_line(int fd, char *str, char **line, int *check)
{
	char	buffer[BUFFER_SIZE + 1];
	char	*tmp;
	int		r;

	r = 1;
	while (r > 0)
	{
		r = read(fd, buffer, BUFFER_SIZE);
		if (r <= 0)
			break ;
		buffer[r] = '\0';
		tmp = str;
		str = ft_strjoin(str, buffer);
		ft_memdel((void **)&tmp);
		if (ft_strchr(str, '\n'))
			break ;
	}
	return (ft_realloc_str(str, line, check));
}

int	get_next_line(int fd, char **line)
{
	static char	*strs[FD_LIMIT];
	int			check;

	if (fd < 0 || fd >= FD_LIMIT || read(fd, strs[fd], 0)
		|| BUFFER_SIZE <= 0 || !line)
		return (GNL_ERROR);
	check = GNL_EOF;
	if (strs[fd] && ft_strchr(strs[fd], '\n'))
	{
		strs[fd] = ft_realloc_str(strs[fd], line, &check);
		return (check);
	}
	if (!strs[fd])
	{
		strs[fd] = ft_strdup("");
		if (!strs[fd])
			return (GNL_ERROR);
	}
	strs[fd] = ft_read_line(fd, strs[fd], line, &check);
	return (check);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_basename.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besellem <besellem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 22:23:34 by besellem          #+#    #+#             */
/*   Updated: 2022/04/19 11:42:50 by besellem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"

#ifdef __linux__
# include <linux/limits.h>
#else
# include <limits.h>
#endif

static char	*__handle_basename_case__(const char *path,
	char *_buf, size_t _size, char *ptr)
{
	char	*tmp;
	size_t	i;

	tmp = ptr;
	while (tmp != path && *tmp == '/')
		--tmp;
	if (tmp == path)
		return (ft_strncpy(_buf, "/", _size));
	ft_strncpy(_buf, path, _size);
	i = ft_strlen(_buf);
	tmp = ptr;
	while (tmp != path && *tmp == '/')
	{
		_buf[--i] = 0;
		--tmp;
	}
	ptr = ft_strrchr(_buf, '/');
	if (ptr)
		return (ptr + 1);
	else
		return (_buf);
}

char	*ft_basename(const char *path)
{
	static char	_buf[PATH_MAX];
	char		*ptr;

	ft_bzero(_buf, sizeof(_buf));
	if (!path || !*path)
		return (ft_strncpy(_buf, ".", sizeof(_buf)));
	ptr = ft_strrchr(path, '/');
	if (!ptr)
		return ((char *)path);
	if ('/' == *ptr && 0 == *(ptr + 1))
		return (__handle_basename_case__(path, _buf, sizeof(_buf), ptr));
	else
		return (ptr + 1);
}

/* does not pass the norm, but is cleaner than the code above */
// char	*ft_basename(const char *path)
// {
// 	static char	_p[PATH_MAX];
// 	char		*ptr;
// 	char		*tmp;
// 	size_t		i;

// 	ft_bzero(_p, sizeof(_p));
// 	if (!path || !*path)
// 		return (ft_strncpy(_p, ".", sizeof(_p)));
// 	ptr = ft_strrchr(path, '/');
// 	if (!ptr)
// 		return ((char *)path);
// 	if ('/' == *ptr && 0 == *(ptr + 1))
// 	{
// 		for (tmp = ptr; tmp != path && *tmp == '/'; --tmp);
// 		if (tmp == path)
// 			return (ft_strncpy(_p, "/", sizeof(_p)));
// 		ft_strncpy(_p, path, sizeof(_p));
// 		i = ft_strlen(_p);
// 		for (tmp = ptr; tmp != path && *tmp == '/'; --tmp, --i)
// 			_p[i - 1] = 0;
// 		ptr = ft_strrchr(_p, '/');
// 		return (ptr ? ptr + 1 : _p);
// 	}
// 	else
// 		return (ptr + 1);
// }

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert_file.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besellem <besellem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 23:01:43 by besellem          #+#    #+#             */
/*   Updated: 2022/03/28 23:02:14 by besellem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_stdio.h"
#include "ft_list.h"

char	**ft_convert_file(int fd)
{
	char	**s;
	char	*line;
	t_list	*lst;
	int		ret;

	lst = NULL;
	line = NULL;
	ret = 1;
	while (ret > 0)
	{
		ret = get_next_line(fd, &line);
		if (ret < 0)
		{
			ft_lstclear(&lst, &free);
			return (NULL);
		}
		ft_lst_push_back(&lst, line);
	}
	s = ft_lst2strs(lst);
	ft_lstclear(&lst, &free);
	return (s);
}

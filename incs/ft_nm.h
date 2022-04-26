/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besellem <besellem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 14:38:46 by besellem          #+#    #+#             */
/*   Updated: 2022/04/26 15:32:57 by besellem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_NM_H
# define FT_NM_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <errno.h>
#include <libft.h>

#if defined(__APPLE__) && defined(__MACH__)
# define FILE_BY_DEFAULT  "a.out"
# include <mach-o/loader.h>
#endif


typedef struct s_file
{
	int				fd;
	void			*p;
	struct stat		st;
}	t_file;


#endif

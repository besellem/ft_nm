/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besellem <besellem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 00:14:58 by besellem          #+#    #+#             */
/*   Updated: 2021/04/19 12:00:40 by besellem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

/*
** -- Defines --
** Limit on how many fds may be opened at the same time
*/
# ifndef FD_LIMIT
#  define FD_LIMIT     512
# endif

/*
** Bytes read
*/
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE  1024
# endif

# define GNL_OK        1
# define GNL_EOF       0
# define GNL_ERROR     (-1)

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stdio.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besellem <besellem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 11:25:41 by besellem          #+#    #+#             */
/*   Updated: 2022/04/12 10:54:49 by besellem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_STDIO_H
# define FT_STDIO_H

# include <unistd.h>

# include "parse_args.h"
# include "../srcs/stdio/ft_printf/incs/ft_printf.h"

void			ft_putn(int c, int bytes);
void			ft_putn_fd(int fd, int c, int bytes);
void			ft_putnbr(int n);
void			ft_putnbr_fd(int n, int fd);
void			ft_putaddr(void *addr);
void			ft_putaddr_fd(void *addr, int fd);

void			ft_putc(int c);
void			ft_putc_fd(int c, int fd);
void			ft_putchar(char c);
void			ft_putchar_fd(char c, int fd);
void			ft_putstr(char *s);
void			ft_putstr_fd(char *s, int fd);
void			ft_putnstr(char *s, size_t n);
void			ft_putnstr_fd(char *s, int fd, size_t n);
void			ft_putendl(char *s);
void			ft_putendl_fd(char *s, int fd);

char			**ft_convert_file(int fd);
int				get_next_line(int fd, char **line);

/* -- FT_BUFFER -- */

/* size to bufferize in `ft_buff*' functions */
# define __BUFF_SIZE__ 4096

/* flag used in `ft_init_buff' to reinit the buffer */
# define BUF_INIT      0x1

typedef struct s_buffer
{
	int			__fd;
	size_t		__index;
	char		*__buff;
}	t_buffer;

typedef struct s_buffer_attr
{
	int				fd;
	unsigned int	oflag;
}	t_buffer_attr;

/*
** -- ft_init_buff
**
** Initialize the static buffer. You can pass some attributes:
**   - fd :    a file descriptor
**   - oflag : a flag to reinitialize the buffer
** May be called with `NULL'.
** You're not obligated to call this function before using any of the ft_buff*
** functions, they will for you.
** By default, the buffer is printed in STDOUT (file descriptor == 1).
*/
t_buffer		*ft_init_buff(const t_buffer_attr *attr);

/*
** -- ft_destroy_buff
**
** Reinit the buffer and free its memory.
*/
void			ft_destroy_buff(void);

/*
** -- ft_buffaddc
**
** Add a single character to the buffer and print the latter if it's full.
*/
int				ft_buffaddc(char c);

/*
** -- ft_buffadd
**
** Add a string to the buffer.
*/
int				ft_buffadd(const char *s);

/*
** -- ft_flush_buff
**
** Flush (print) the buffer even if it's not full and release its memory
** (calls `ft_destroy_buff').
*/
int				ft_flush_buff(void);

#endif

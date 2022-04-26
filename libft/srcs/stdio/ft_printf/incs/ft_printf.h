/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besellem <besellem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 00:10:55 by besellem          #+#    #+#             */
/*   Updated: 2022/04/04 15:57:30 by besellem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

/*
** -- INCLUDES --
*/
# include <libft.h>
# include "ft_printf_internal.h"

/*
** -- PROTOTYPES --
*/
int	ft_printf(const char *format, ...)
	__attribute__((format(printf, 1, 2)));

int	ft_dprintf(int fd, const char *format, ...)
	__attribute__((format(printf, 2, 3)));

int	ft_sprintf(char *str, const char *format, ...)
	__attribute__((format(printf, 2, 3)));

int	ft_snprintf(char *str, size_t size, const char *format, ...)
	__attribute__((format(printf, 3, 4)));

int	ft_asprintf(char **ret, const char *format, ...)
	__attribute__((format(printf, 2, 3)));

int	ft_vprintf(const char *format, va_list ap)
	__attribute__((format(printf, 1, 0)));

int	ft_vdprintf(int fd, const char *format, va_list ap)
	__attribute__((format(printf, 2, 0)));

int	ft_vsprintf(char *str, const char *format, va_list ap)
	__attribute__((format(printf, 2, 0)));

int	ft_vsnprintf(char *str, size_t size, const char *format, va_list ap)
	__attribute__((format(printf, 3, 0)));

int	ft_vasprintf(char **ret, const char *format, va_list ap)
	__attribute__((format(printf, 2, 0)));

#endif

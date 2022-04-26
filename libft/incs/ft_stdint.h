/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stdint.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besellem <besellem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 13:42:44 by besellem          #+#    #+#             */
/*   Updated: 2022/04/26 14:59:48 by besellem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_STDINT_H
# define FT_STDINT_H

# include <stdint.h>

# if !defined(__CLANG_STDINT_H)

typedef signed char				t_int8;
typedef short					t_int16;
typedef int						t_int32;
typedef long long				t_int64;

typedef unsigned char			t_uint8;
typedef unsigned short			t_uint16;
typedef unsigned int			t_uint32;
typedef unsigned long long		t_uint64;

# else

typedef int8_t					t_int8;
typedef int16_t					t_int16;
typedef int32_t					t_int32;
typedef int64_t					t_int64;

typedef uint8_t					t_uint8;
typedef uint16_t				t_uint16;
typedef uint32_t				t_uint32;
typedef uint64_t				t_uint64;

# endif

/*
** __int128_t is a 16 bytes type, wider than an `unsigned long long' (8 bytes),
** it is defined by gcc or gcc on certain versions.
*/
# if defined(__SIZEOF_INT128__)

typedef __int128_t				t_wide_int;
typedef __uint128_t				t_uwide_int;

# else

typedef intmax_t				t_wide_int;
typedef uintmax_t				t_uwide_int;

# endif

/*
** macros for bit tricks
*/
# if __SIZE_WIDTH__ == 64
#  define LOWS  0x0101010101010101
#  define HIGHS 0x8080808080808080
# else
#  define LOWS  0x01010101
#  define HIGHS 0x80808080
# endif

#endif

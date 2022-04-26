/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defs.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besellem <besellem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/09 21:09:44 by besellem          #+#    #+#             */
/*   Updated: 2022/04/08 18:00:01 by besellem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFS_H
# define DEFS_H

# include <sys/cdefs.h>

/*
** When LIBC_NO_CRASH_ON_NULL is set to 1 (default), it is used to handle
** the cases where the libc actually segfault by passing a NULL ptr.
**
** When defined, we can use ft_strlen(NULL), ft_strdup(NULL),
** or ft_strchr(NULL, 42), for example, without segfault.
**
** However, if you want to crash where the libc is crashing, use the flag
** `-D LIBC_NO_CRASH_ON_NULL=0' at compile time.
*/
# if !defined(LIBC_NO_CRASH_ON_NULL)
#  define LIBC_NO_CRASH_ON_NULL  1
# else
#  define LIBC_NO_CRASH_ON_NULL  0
# endif

/*
** Useful macro to print out a message with a ft_printf or a write for example.
** Does not pass the norm unfortunately. Useful in the debugging process though.
**
** # define ERR  printf("\e[1;31m%s:%d:\e[0m Here\n", __FILE__, __LINE__);
*/

/*
** Define TRUE and FALSE macros
*/
# ifndef TRUE
#  define TRUE   1
# endif

# ifndef FALSE
#  define FALSE  0
# endif

/*
** Most of syscalls return -1 on errors
*/
# define SYSCALL_ERR (-1)

/*
** Memory page size
*/
# ifndef PAGE_SIZE
#  define PAGE_SIZE  4096
# endif

/*
** Force compiler to do inlining even without the -O flags
** Does not pass the norm...
*/
// # if defined(__has_attribute)
// #  if __has_attribute(__always_inline__)
// #   define __INLINE_ATTR__   __attribute__((__always_inline__))
// #  elif __has_attribute(always_inline)
// #   define __INLINE_ATTR__   __attribute__((always_inline))
// #  else
// #   define __INLINE_ATTR__
// #  endif
// # else
// #  define __INLINE_ATTR__
// # endif

// # define __INLINE            __INLINE_ATTR__ inline

# define __INLINE            inline

# ifndef __constructor
#  define __constructor       __attribute__((constructor))
# endif

# ifndef __destructor
#  define __destructor        __attribute__((destructor))
# endif

#endif

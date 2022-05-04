/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besellem <besellem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 14:38:46 by besellem          #+#    #+#             */
/*   Updated: 2022/05/04 15:15:17 by besellem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_NM_H
# define FT_NM_H


#ifndef __linux__
# error "This program is only for Linux"
#endif


#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <errno.h> // to remove
#include <elf.h>
#include <libft.h>


/*
** -- GLOBALS --
*/

extern char				*g_prog_name;
extern t_parsing_opts	g_opts;


/*
** -- DEFINES --
*/

#if 1
# define DEBUG
#endif

#ifndef __unused
# define __unused __attribute__((unused))
#endif

#ifdef DEBUG
# define LOG ft_dprintf(2, B_GREEN"%s:%d:"CLR_COLOR" %s()\n", __FILE__, __LINE__, __func__);
#else
# define LOG
#endif


#define get_sorting_cmp() \
	(option_set(g_opts.opts, OPT_R_MIN) ? \
		(option_set(g_opts.opts, OPT_N_MIN) ? &sort_addr_desc : &sort_alpha_desc) : \
		(option_set(g_opts.opts, OPT_N_MIN) ? &sort_addr_asc : &sort_alpha_asc))
	


/*
** -- DATA STRUCTURES --
*/

typedef struct
{
	char		type;
	char		*name;
	uint64_t	offset;
}	t_symbol;

CREATE_LST_TYPE(list_t, t_symbol);

typedef struct
{
	int				fd;
	char			*filename;
	int				class;
	void			*p;
	struct stat		st;
}	t_file;


/*
** -- PROTOTYPES --
*/

/* utils */
int		init_file(const char *, t_file *);
void	destroy_file(t_file *);
int		find_elf_class(t_file *);
int		elf_check_integrity(const t_file *);
void	elf_display_list(const t_file *, list_t *);

/* utils - sorting */
int		sort_alpha_asc(t_symbol, t_symbol);
int		sort_alpha_desc(t_symbol, t_symbol);
int		sort_addr_asc(t_symbol, t_symbol);
int		sort_addr_desc(t_symbol, t_symbol);


// TODO: to remove
	void	print_Ehdr(const Elf64_Ehdr *);
	void	print_Phdr(const Elf64_Phdr *);
	void	print_Shdr(const Elf64_Shdr *);
	void	print_Sym(const Elf64_Sym *);
// end to remove


/* elf64 */
void	elf64_exec(const t_file *);



#endif

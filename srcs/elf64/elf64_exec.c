/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elf64_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besellem <besellem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 20:22:06 by besellem          #+#    #+#             */
/*   Updated: 2022/04/26 21:33:48 by besellem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

static char		elf64_get_sym_type(const Elf64_Sym *sym)
{
	switch (sym->st_info)
	{
		case STT_FILE: return 'a';

		default:
			break;
	}

	switch (ELF64_ST_BIND(sym->st_info))
	{
		case STB_GLOBAL: return 'G';
		case STB_LOCAL:  return 'L';
		case STB_WEAK:   return 'W';
		
		default:         return '?';
	}
}

static list_t	*elf64_get_symtab(const t_file *file, const Elf64_Shdr *shdr, size_t idx)
{
	const Elf64_Sym		*symtab = file->p + shdr[idx].sh_offset;
	list_t				*tab = NULL;

	for (size_t i = 0; i < (shdr[idx].sh_size / shdr[idx].sh_entsize); ++i)
	{
		char		*strtab = file->p + shdr[shdr[idx].sh_link].sh_offset;
		t_symbol	sym = {0};

		sym.type = elf64_get_sym_type(&symtab[i]);
		sym.name = strtab + symtab[i].st_name;
		sym.offset = symtab[i].st_value;
		
		if (!*sym.name)
			continue ;

		lst_push_sorted(&tab, sym, get_sorting_cmp());

		ft_printf("[%s]\n", sym.name);
		print_Sym(&symtab[i]);
	}
	return tab;
}

static void	elf64_print_symtab(const t_file *file, list_t *symtab)
{
	t_symbol	sym;

	for (list_t *lst = symtab; lst != NULL; lst = lst->next)
	{
		sym = lst->content;
		
		if (option_set(g_opts.opts, OPT_O_MIN))
			ft_printf("%s:", file->filename);

		if (0 == sym.offset)
		{
			ft_printf("%16.d %c %s\n", 0, sym.type, sym.name);
		}
		else
		{
			ft_printf("%016lx %c %s\n", sym.offset, sym.type, sym.name);
		}
	}
}

void	elf64_exec(const t_file *file, bool print_header)
{
	__unused const Elf64_Ehdr	*hdr = file->p;
	__unused const Elf64_Phdr	*phdr = file->p + hdr->e_phoff;
	__unused Elf64_Shdr			*shdr = file->p + hdr->e_shoff;
	list_t						*symtab;
	size_t						symbols_nb = 0;

	if (print_header)
		ft_printf("\n%s:\n", file->filename);

	// print_Ehdr(hdr);
	// print_Phdr(phdr);

	for (int i = 0; i < hdr->e_shnum; ++i)
	{
		if (SHT_SYMTAB == shdr[i].sh_type)
		{
			symtab = elf64_get_symtab(file, shdr, i);
			elf64_print_symtab(file, symtab);
			lst_clear(&symtab, LST_CLEAR_IGN);
			++symbols_nb;
		}
	}

	if (0 == symbols_nb)
	{
		ft_dprintf(STDERR_FILENO, "%s: %s: no symbols\n",
			g_prog_name, file->filename);
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elf64_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besellem <besellem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 20:22:06 by besellem          #+#    #+#             */
/*   Updated: 2022/05/04 17:42:00 by besellem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

static char		elf64_get_sym_type(const Elf64_Shdr *shdr, const Elf64_Sym sym)
{
	const unsigned char	_info = sym.st_info;
	Elf64_Word			_type = 0;
	Elf64_Xword			_flags = 0;
	char				type;

	// avoid special section indexes (avoiding segfault by the way)
	// TODO: to check
	if (sym.st_shndx != SHN_UNDEF &&
		sym.st_shndx != SHN_LORESERVE &&
		sym.st_shndx != SHN_LOPROC &&
		sym.st_shndx != SHN_HIPROC &&
		sym.st_shndx != SHN_ABS &&
		sym.st_shndx != SHN_COMMON &&
		sym.st_shndx != SHN_HIRESERVE)
	{
		_type = shdr[sym.st_shndx].sh_type;
		_flags = shdr[sym.st_shndx].sh_flags;
	}

	if (ELF64_ST_BIND(_info) == STB_GNU_UNIQUE)
		type = 'u';
	else if (ELF64_ST_BIND(_info) == STB_WEAK)
		type = sym.st_shndx == SHN_UNDEF ? 'w' : 'W';
	else if (ELF64_ST_BIND(_info) == STB_WEAK && ELF64_ST_TYPE(_info) == STT_OBJECT)
		type = sym.st_shndx == SHN_UNDEF ? 'v' : 'V';
	else if (sym.st_shndx == SHN_UNDEF)
		type = 'U';
	else if (sym.st_shndx == SHN_ABS)
		type = 'A';
	else if (sym.st_shndx == SHN_COMMON)
		type = 'C';
	else if (_type == SHT_NOBITS && _flags == (SHF_ALLOC | SHF_WRITE))
		type = 'B';
	else if (_type == SHT_PROGBITS && (_flags == SHF_ALLOC || _flags == (SHF_ALLOC | SHF_MERGE)))
		type = 'R';
	else if ((_type == SHT_PROGBITS && _flags == (SHF_ALLOC | SHF_WRITE)) ||
			 _type == SHT_DYNAMIC || _type == SHT_INIT_ARRAY || _type == SHT_FINI_ARRAY ||
			 (ELF64_ST_BIND(_info) == STB_GLOBAL && _type == STT_OBJECT && sym.st_shndx == SHN_UNDEF))
		type = 'D';
	else if (_type == SHT_PROGBITS || _type == SHT_INIT_ARRAY || _type == SHT_FINI_ARRAY)
		type = 'T';
	else
		type = '?';
	
	if (ELF64_ST_BIND(_info) == STB_LOCAL )
		type = ft_tolower(type);
	
	return type;
}

static list_t	*elf64_get_symtab(const t_file *file, const Elf64_Shdr *shdr, size_t idx)
{
	const Elf64_Sym		*symtab = file->p + shdr[idx].sh_offset;
	const char			*strtab = file->p + shdr[shdr[idx].sh_link].sh_offset;
	list_t				*tab = NULL;


	// const size_t	_sz = shdr[shdr[idx].sh_link].sh_size;
	// char			*_p = (char *)strtab + _sz + 1;
	// size_t			len = 0;
		
	// for (int i = 0; *_p; ++i)
	// {
	// 	t_symbol	sym = {0};
		
	// 	sym.name = _p;
	// 	sym.type = 'n';
	// 	len = ft_strlen(_p);
		
	// 	// -p option
	// 	if (option_set(g_opts.opts, OPT_P_MIN))
	// 	{
	// 		lst_push_back(&tab, sym);
	// 	}
	// 	else
	// 	{
	// 		lst_push_sorted(&tab, sym, get_sorting_cmp());
	// 	}
	// 	_p += len + 1;
	// }

	
	for (size_t i = 0; i < (shdr[idx].sh_size / sizeof(Elf64_Sym)); ++i)
	{
		t_symbol	sym = {0};

		// -a option
		if (symtab[i].st_shndx == SHN_ABS && !option_set(g_opts.opts, OPT_A_MIN))
			continue ;

		sym.type = elf64_get_sym_type(shdr, symtab[i]);
		sym.name = (char *)strtab + symtab[i].st_name;
		sym.offset = symtab[i].st_value;
		
		// empty name
		if (!sym.name || !*sym.name)
			continue ;

		// -g option
		if (ft_islower(sym.type) && sym.type != 'w' && option_set(g_opts.opts, OPT_G_MIN))
			continue ;
		
		// -u option
		if (symtab[i].st_shndx != SHN_UNDEF && option_set(g_opts.opts, OPT_U_MIN))
			continue ;

		// -p option
		if (option_set(g_opts.opts, OPT_P_MIN))
		{
			lst_push_back(&tab, sym);
		}
		else
		{
			lst_push_sorted(&tab, sym, get_sorting_cmp());
		}
	}
	return tab;
}

void	elf64_exec(const t_file *file)
{
	const Elf64_Ehdr	*hdr = file->p;
	Elf64_Shdr			*shdr = file->p + hdr->e_shoff;
	size_t				symbols_nb = 0;
	list_t				*symtab;

	for (size_t i = 0; i < hdr->e_shnum; ++i)
	{
		// if (SHT_NULL == shdr[i].sh_type)
		// 	continue ;

		if (SHT_SYMTAB == shdr[i].sh_type)
		{
			symtab = elf64_get_symtab(file, shdr, i);
			elf_display_list(file, symtab);
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

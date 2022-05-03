/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elf64_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besellem <besellem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 20:22:06 by besellem          #+#    #+#             */
/*   Updated: 2022/05/03 11:04:08 by besellem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

static
char		elf64_get_sym_type(const Elf64_Shdr *shdr, const Elf64_Sym sym)
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
			 _type == SHT_DYNAMIC ||
			 (ELF64_ST_BIND(_info) == STB_GLOBAL && _type == STT_OBJECT && sym.st_shndx == SHN_UNDEF))
		type = 'D';
	else if (_type == SHT_PROGBITS || _type == SHT_INIT_ARRAY || _type == SHT_FINI_ARRAY)
		type = 'T';
	else
		type = '?';
	
	if (ELF64_ST_BIND(_info) == STB_LOCAL && type != '?')
		type += 32;
	
	return type;
}

static
list_t	*elf64_get_symtab(const t_file *file, const Elf64_Shdr *shdr, size_t idx)
{
	const Elf64_Sym		*symtab = file->p + shdr[idx].sh_offset;
	const char			*strtab = file->p + shdr[shdr[idx].sh_link].sh_offset;
	list_t				*tab = NULL;

	// ft_printf("size: %zu, %zu\n",
	// 	shdr[idx].sh_size / sizeof(Elf64_Sym),
	// 	shdr[idx].sh_size / shdr[idx].sh_entsize);
	
	for (size_t i = 0; i < (shdr[idx].sh_size / sizeof(Elf64_Sym)); ++i)
	{
		t_symbol	sym = {0};

		// ft_printf("offset: %#lx\n", shdr[shdr[idx].sh_link].sh_offset);
		// ft_printf("offset: %#6x %6u\n", symtab[i].st_shndx, symtab[i].st_shndx);
		
		if (symtab[i].st_shndx == SHN_ABS && !option_set(g_opts.opts, OPT_A_MIN))
			continue ;

		sym.type = elf64_get_sym_type(shdr, symtab[i]);
		sym.name = (char *)strtab + symtab[i].st_name;
		sym.offset = symtab[i].st_value;
		

		if (ft_islower(sym.type) && sym.type != 'w' && option_set(g_opts.opts, OPT_G_MIN))
			continue ;

		// empty name
		if (!sym.name || !*sym.name)
			continue ;

		lst_push_sorted(&tab, sym, get_sorting_cmp());
		
		// ft_printf("[%s]\n", sym.name);
		// print_Sym(&symtab[i]);
	}
	return tab;
}

static
void	elf64_print_symtab(const t_file *file, list_t *symtab)
{
	t_symbol	sym;

	for (list_t *lst = symtab; lst != NULL; lst = lst->next)
	{
		sym = lst->content;
		
		if (option_set(g_opts.opts, OPT_O_MIN))
			ft_printf("%s:", file->filename);

		if ('U' == sym.type || 0 == sym.offset)
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
	__unused const Elf64_Ehdr		*hdr = file->p;
	__unused const Elf64_Phdr		*phdr = file->p + hdr->e_phoff;
	__unused Elf64_Shdr				*shdr = file->p + hdr->e_shoff;
	__unused size_t					symbols_nb = 0;
	__unused list_t					*symtab;

	if (print_header)
		ft_printf("\n%s:\n", file->filename);

	// print_Ehdr(hdr);
	// print_Phdr(phdr);

	for (size_t i = 0; i < hdr->e_shnum; ++i)
	{
		if (SHT_SYMTAB == shdr[i].sh_type)// || SHT_NOBITS == shdr[i].sh_type)
		{
			symtab = elf64_get_symtab(file, shdr, i);
			elf64_print_symtab(file, symtab);
			lst_clear(&symtab, LST_CLEAR_IGN);
			++symbols_nb;
		}
		// if (SHT_NOBITS == shdr[i].sh_type)
		// if (SHT_DYNAMIC == shdr[i].sh_type)
		// {
		// 	symtab = elf64_get_symtab(file, shdr, i);
		// 	// elf64_print_symtab(file, symtab);
		// 	lst_clear(&symtab, LST_CLEAR_IGN);
		// 	++symbols_nb;
		// 	print_Shdr(&shdr[i]);
		// }
	}

	if (0 == symbols_nb)
	{
		ft_dprintf(STDERR_FILENO, "%s: %s: no symbols\n",
			g_prog_name, file->filename);
	}
	// ft_printf("sz: %#lx %#lx\n", 0x00048580UL, hdr->e_shoff);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besellem <besellem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 20:22:59 by besellem          #+#    #+#             */
/*   Updated: 2022/05/03 10:34:44 by besellem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

int		init_file(const char *filename, t_file *file)
{
	errno = 0;

	file->filename = (char *)filename;
	file->fd = open(filename, O_RDONLY);
	if (SYSCALL_ERR == file->fd)
	{
		ft_dprintf(STDERR_FILENO, "%s: '%s': %s\n",
			g_prog_name, filename, strerror(errno));
		return 1;
	}

	if (SYSCALL_ERR == fstat(file->fd, &file->st))
		return 1;

	if (S_ISDIR(file->st.st_mode))
	{
		ft_dprintf(STDERR_FILENO, "%s: Warning: '%s' is a directory\n", g_prog_name, filename);
		return 1;
	}

	// file too small to be valid
	if (file->st.st_size < (long)sizeof(Elf32_Ehdr))
		return 1;

	file->p = mmap(NULL, file->st.st_size, PROT_READ, MAP_SHARED, file->fd, 0);
	if (MAP_FAILED == file->p)
	{
		ft_dprintf(STDERR_FILENO, "%s: %s: %s\n", g_prog_name, filename, strerror(errno));
		return 1;
	}

	return 0;
}

void	destroy_file(t_file *file)
{
	if (file->p)
	{
		if (SYSCALL_ERR == munmap(file->p, file->st.st_size))
			ft_dprintf(STDERR_FILENO, "munmap error: %s\n", strerror(errno));
	}
	if (file->fd)
		close(file->fd);
}

int		find_elf_class(t_file *file)
{
	const Elf64_Ehdr	*hdr = file->p;

	if (ft_memcmp(hdr->e_ident, ELFMAG, SELFMAG))
		return 1;
	if (ELFCLASSNONE == hdr->e_ident[EI_CLASS])
		return 1;

	file->class = hdr->e_ident[EI_CLASS]; // may be ELFCLASS32 or ELFCLASS64
	// ft_printf("[");
	// write(1, hdr->e_ident, sizeof(hdr->e_ident));
	// ft_printf("] [%d]\n", hdr->e_type);
	return 0;
}


// TODO: TO REMOVE
void	print_Ehdr(const Elf64_Ehdr *hdr)
{
	ft_printf("{\n");
	ft_printf("\te_type:        %10d\n", hdr->e_type);
    ft_printf("\te_machine:     %10d\n", hdr->e_machine);
    ft_printf("\te_version:     %10d\n", hdr->e_version);
    ft_printf("\te_entry:       %10ld\n", hdr->e_entry);
    ft_printf("\te_phoff:       %10ld\n", hdr->e_phoff);
    ft_printf("\te_shoff:       %10ld\n", hdr->e_shoff);
    ft_printf("\te_flags:       %10d\n", hdr->e_flags);
    ft_printf("\te_ehsize:      %10d\n", hdr->e_ehsize);
    ft_printf("\te_phentsize:   %10d\n", hdr->e_phentsize);
    ft_printf("\te_phnum:       %10d\n", hdr->e_phnum);
    ft_printf("\te_shentsize:   %10d\n", hdr->e_shentsize);
    ft_printf("\te_shnum:       %10d\n", hdr->e_shnum);
    ft_printf("\te_shstrndx:    %10d\n", hdr->e_shstrndx);
	ft_printf("}\n");
}

void	print_Phdr(const Elf64_Phdr *phdr)
{
	ft_printf("{\n");
	ft_printf("\tp_type:        %10d\n", phdr->p_type);
	ft_printf("\tp_flags:       %10d\n", phdr->p_flags);
	ft_printf("\tp_offset:      %10ld\n", phdr->p_offset);
	ft_printf("\tp_vaddr:       %10ld\n", phdr->p_vaddr);
	ft_printf("\tp_paddr:       %10ld\n", phdr->p_paddr);
	ft_printf("\tp_filesz:      %10ld\n", phdr->p_filesz);
	ft_printf("\tp_memsz:       %10ld\n", phdr->p_memsz);
	ft_printf("\tp_align:       %10ld\n", phdr->p_align);
	ft_printf("}\n");
}

void	print_Shdr(const Elf64_Shdr *shdr)
{
	ft_printf("{\n");
	ft_printf("\tsh_name:       %10d\n", shdr->sh_name);
	ft_printf("\tsh_type:       %10d\n", shdr->sh_type);
	ft_printf("\tsh_flags:      %10ld\n", shdr->sh_flags);
	ft_printf("\tsh_addr:       %10ld\n", shdr->sh_addr);
	ft_printf("\tsh_offset:     %10ld\n", shdr->sh_offset);
	ft_printf("\tsh_size:       %10ld\n", shdr->sh_size);
	ft_printf("\tsh_link:       %10d\n", shdr->sh_link);
	ft_printf("\tsh_info:       %10d\n", shdr->sh_info);
	ft_printf("\tsh_addralign:  %10ld\n", shdr->sh_addralign);
	ft_printf("\tsh_entsize:    %10ld\n", shdr->sh_entsize);
	ft_printf("}\n");
}

void	print_Sym(const Elf64_Sym *sym)
{
	ft_printf("\t{\n");
	ft_printf("\t\tst_name:   %10d\n", sym->st_name);
	ft_printf("\t\tst_info:   %10d\n", sym->st_info);
	ft_printf("\t\tst_other:  %10d\n", sym->st_other);
	ft_printf("\t\tst_shndx:  %10d\n", sym->st_shndx);
	ft_printf("\t\tst_value:  %10ld\n", sym->st_value);
	ft_printf("\t\tst_size:   %10ld\n", sym->st_size);
	ft_printf("\t}\n");
}
// END TO REMOVE

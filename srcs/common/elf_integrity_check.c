/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elf_integrity_check.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besellem <besellem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 17:28:45 by besellem          #+#    #+#             */
/*   Updated: 2022/05/04 22:21:45 by besellem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

static int	_elf32_integrity_check(const t_file *file)
{
	const Elf32_Ehdr	*hdr = file->p;
	const Elf32_Shdr	*shdr = file->p + hdr->e_shoff;

	// file too small to be valid
	if (file->st.st_size < (long)sizeof(*hdr))
		return 1;

	if (ft_memcmp(hdr->e_ident, ELFMAG, SELFMAG))
		return 1;

	if (ELFCLASSNONE == hdr->e_ident[EI_CLASS])
		return 1;

	if ((size_t)file->st.st_size < hdr->e_phoff)
		return 1;

	if ((size_t)file->st.st_size < hdr->e_shoff)
		return 1;

	// file too small for supposed data
	if ((hdr->e_shnum * sizeof(*shdr)) > (size_t)file->st.st_size)
		return 1;
	
	return 0;
}

static int	_elf64_integrity_check(const t_file *file)
{
	const Elf64_Ehdr	*hdr = file->p;
	const Elf64_Shdr	*shdr = file->p + hdr->e_shoff;

	// file too small to be valid
	if (file->st.st_size < (long)sizeof(*hdr))
		return 1;

	if (ft_memcmp(hdr->e_ident, ELFMAG, SELFMAG))
		return 1;

	if (ELFCLASSNONE == hdr->e_ident[EI_CLASS])
		return 1;

	if ((size_t)file->st.st_size < hdr->e_phoff)
		return 1;

	if ((size_t)file->st.st_size < hdr->e_shoff)
		return 1;

	// file too small for supposed data
	if ((hdr->e_shnum * sizeof(*shdr)) > (size_t)file->st.st_size)
		return 1;
	
	return 0;
}

int			elf_integrity_check(const t_file *file)
{
	if (ELFCLASS32 == file->class)
	{
		return _elf32_integrity_check(file);
	}
	else if (ELFCLASS64 == file->class)
	{
		return _elf64_integrity_check(file);
	}
	return 1;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elf_file.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besellem <besellem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 17:30:29 by besellem          #+#    #+#             */
/*   Updated: 2022/05/04 17:36:27 by besellem         ###   ########.fr       */
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
		ft_dprintf(STDERR_FILENO, "%s: Warning: '%s' is a directory\n",
			g_prog_name, filename);
		return 1;
	}

	if (file->st.st_size <= 0)
		return 1;
	
	// checked here too because we set file->class below
	if (file->st.st_size < (long)sizeof(Elf64_Ehdr))
		return 1;
	
	file->p = mmap(NULL, file->st.st_size, PROT_READ, MAP_SHARED, file->fd, 0);
	if (MAP_FAILED == file->p)
	{
		ft_dprintf(STDERR_FILENO, "%s: %s: mmap failed\n",
			g_prog_name, filename);
		return 1;
	}
	
	file->class = ((Elf64_Ehdr *)(file->p))->e_ident[EI_CLASS];
	
	return 0;
}

void	destroy_file(t_file *file)
{
	if (file->p)
	{
		if (SYSCALL_ERR == munmap(file->p, file->st.st_size))
			ft_dprintf(STDERR_FILENO, "munmap error\n");
	}
	if (file->fd != -1)
		close(file->fd);
}

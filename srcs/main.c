/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besellem <besellem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 14:40:44 by besellem          #+#    #+#             */
/*   Updated: 2022/04/26 15:45:06 by besellem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

// int		find_bin_type(const t_file *file)
// {
	
// }

void	close_file(t_file *file)
{
	if (file->p)
	{
		if (SYSCALL_ERR == munmap(file->p, file->st.st_size))
			ft_dprintf(2, "munmap error: %s\n", strerror(errno));
	}
	if (file->fd)
		close(file->fd);
}

int		open_file(const char *prog_name, const char *filename, t_file *file)
{
	file->fd = open(filename, O_RDONLY);
	if (SYSCALL_ERR == file->fd)
	{
		ft_dprintf(STDERR_FILENO, "%s: %s: %s\n", prog_name, filename, strerror(errno));
		return (1);
	}

	if (SYSCALL_ERR == fstat(file->fd, &file->st))
	{
		ft_dprintf(STDERR_FILENO, "%s: %s: %s\n", prog_name, filename, strerror(errno));
		return (1);
	}

	file->p = mmap(NULL, file->st.st_size, PROT_READ, MAP_PRIVATE, file->fd, 0);
	if (MAP_FAILED == file->p)
	{
		ft_dprintf(STDERR_FILENO, "%s: %s: %s\n", prog_name, filename, strerror(errno));
		return (1);
	}

	return (0);
}

void	exec_on_file(const char *prog_name, const char *filename)
{
	t_file	file = {0};

	if (open_file(prog_name, filename, &file))
		return ;

	if (file.st.st_size < (int)sizeof(struct mach_header))
	{
		ft_printf("%s: %s: File too small to be valid\n", prog_name, filename);
		return ;
	}
	// if (find_bin_type(&file))
	// {
	// 	ft_printf("%s: %s: File type not supported\n", prog_name, filename);
	// 	return ;
	// }

	// write(1, file.p, file.st.st_size);

	close_file(&file);
}

int		main(int ac, char **av)
{
	const char		*prog_name = ft_basename(av[0]);
	t_parsing_opts	opts;

	opts = parse_args(ac, av, true, "agurp");
	if (option_set(opts.opts, OPT_ILLEGAL))
	{
		ft_dprintf(STDERR_FILENO, "%s: illegal option -- %c\n",
				   prog_name, find_option_symbol(opts.opts & ~OPT_ILLEGAL));
		return (1);
	}


	if (opts.end_pos == ac)
	{
		exec_on_file(prog_name, FILE_BY_DEFAULT);
		return (0);
	}

	for (int i = opts.end_pos; i < ac; ++i)
	{
		exec_on_file(prog_name, av[i]);
	}
	
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besellem <besellem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 14:40:44 by besellem          #+#    #+#             */
/*   Updated: 2022/04/26 21:31:03 by besellem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

char				*g_prog_name;
t_parsing_opts		g_opts;

int		ft_nm(const char *filename, bool print_header)
{
	t_file	file = {0};

	if (init_file(filename, &file))
		return 1;
	
	if (find_elf_class(&file))
	{
		ft_printf("%s: %s: file format not recognized\n", g_prog_name, filename);
		return 1;
	}

	// ft_printf("class: %d\n", file.class == ELFCLASS32 ? 32 : 64);
	
	// if (ELFCLASS32 == file.class)
	// 	elf32_exec(&file, print_header);
	// else if (ELFCLASS64 == file.class)
	// 	elf64_exec(&file, print_header);
	if (ELFCLASS64 == file.class)
		elf64_exec(&file, print_header);

	destroy_file(&file);
	return 0;
}

int		main(int ac, char **av)
{
	bool	errors = false;

	g_prog_name = ft_basename(av[0]);

	/* parse arguments */
	g_opts = parse_args(ac, av, true, "agunorp");

	/* if there's an illegal option found, quit properly */
	if (option_set(g_opts.opts, OPT_ILLEGAL))
	{
		ft_dprintf(STDERR_FILENO, "%s: illegal option -- %c\n",
				   g_prog_name, find_option_symbol(g_opts.opts & ~OPT_ILLEGAL));
		return 1;
	}


	/* if there's no file provided, try ft_nm on ./a.out */
	if (g_opts.end_pos == ac)
	{
		errors |= ft_nm("a.out", false);
	}
	else
	{
		for (int i = g_opts.end_pos; i < ac; ++i)
		{
			errors |= ft_nm(av[i], (ac - g_opts.end_pos > 1));
		}
	}
	
	return errors;
}

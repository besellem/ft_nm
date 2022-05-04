/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elf_display.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besellem <besellem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 17:44:52 by besellem          #+#    #+#             */
/*   Updated: 2022/05/04 17:45:32 by besellem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

void	elf_display_list(const t_file *file, list_t *symtab)
{
	t_symbol	sym;

	for (list_t *lst = symtab; lst != NULL; lst = lst->next)
	{
		sym = lst->content;
		
		// -o option
		if (option_set(g_opts.opts, OPT_O_MIN))
			ft_printf("%s:", file->filename);

		if (sym.offset > 0 ||
			't' == ft_tolower(sym.type) ||
			'a' == ft_tolower(sym.type) ||
			'b' == ft_tolower(sym.type))//|| 'U' == sym.type || 0 == sym.offset)
		{
			ft_printf("%016lx %c %s\n", sym.offset, sym.type, sym.name);
		}
		else
		{
			ft_printf("%16.d %c %s\n", 0, sym.type, sym.name);
		}
	}
}

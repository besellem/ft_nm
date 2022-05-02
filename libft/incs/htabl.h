/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   htabl.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besellem <besellem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/01 16:24:45 by besellem          #+#    #+#             */
/*   Updated: 2022/05/01 23:42:20 by besellem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HTABL_H
# define HTABL_H

# include <stdlib.h>
# include "list_templates.h"

typedef struct s_htabl			t_htabl;
typedef struct s_htabl_node		t_htabl_node;

struct s_htabl_node
{
	char	*key;
	void	*value;
};

CREATE_LST_TYPE(t_htabl_lst, t_htabl_node *)

struct s_htabl
{
	size_t		_size;
	void		(*_del_node)(t_htabl_node *);
	t_htabl_lst	**_root;
};

t_htabl			*htabl_new(void (*del_node)(t_htabl_node *));
t_htabl_node	*htabl_insert(t_htabl **ht, char *key, void *value);
void			htabl_destroy(t_htabl **ht);
void			*htabl_search(const t_htabl *ht, const char *key);
size_t			htabl_hash(const char *key);
void			htabl_print(const t_htabl *ht, void (*print_val)());

#endif

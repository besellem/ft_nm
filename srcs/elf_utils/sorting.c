/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sorting.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besellem <besellem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 21:29:05 by besellem          #+#    #+#             */
/*   Updated: 2022/04/26 21:40:13 by besellem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

int		sort_alpha_asc(t_symbol a, t_symbol b)
{
	return ft_strcmp(a.name, b.name);
}

int		sort_alpha_desc(t_symbol a, t_symbol b)
{
	return sort_alpha_asc(b, a);
}

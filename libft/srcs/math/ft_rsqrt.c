/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rsqrt.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besellem <besellem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 23:22:44 by besellem          #+#    #+#             */
/*   Updated: 2021/12/08 23:33:28 by besellem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_math.h"

/*
** Computes 1/√x
** https://en.wikipedia.org/wiki/Fast_inverse_square_root
*/

float	ft_rsqrtf(float x)
{
	const float	x2 = x * 0.5F;
	float		y;
	int			i;

	y = x;
	i = *(int *)&y;
	i = 0x5f3759df - (i >> 1);
	y = *(float *)&i;
	y = y * (1.5F - (x2 * y * y));
	return (y);
}

double	ft_rsqrt(double x)
{
	const double	x2 = x * 0.5;
	double			y;
	long			i;

	y = x;
	i = *(long *)&y;
	i = 0x5fe6eb50c7b537a9 - (i >> 1);
	y = *(double *)&i;
	y = y * (1.5 - (x2 * y * y));
	return (y);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_proc_perlin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoussa <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/04 15:56:28 by mmoussa           #+#    #+#             */
/*   Updated: 2019/07/11 19:05:39 by oboutrol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include <math.h>

t_vector			rt_perlin_marble(float u, float v, t_texture text)
{
	double		perl;
	t_vector	c[2];

	(void)text;
	perl = 1 - sqrt(fabs(cos(2 * M_PI *
		rt_perlin2d(u, v, text.pfrequ, text.pdepth))));
	c[0] = (t_vector) {0.15, 0.15, 0.15};
	c[1] = (t_vector) {1, 1, 1};
	return (ft_vadd(ft_vmul(c[1], 1 - perl), ft_vmul(c[0], perl)));
}

t_vector			rt_perlin_lava(float u, float v, t_texture text)
{
	double		perl;

	(void)text;
	perl = 1 - sqrt(fabs(2 * M_PI *
		rt_perlin2d(u, v, text.pfrequ, text.pdepth)));
	return ((t_vector) {0.1 * perl, perl, perl});
}

t_vector			rt_perlin_sand(float u, float v, t_texture text)
{
	double		perl;

	(void)text;
	perl = rt_perlin2d(u, v, text.pfrequ, text.pdepth);
	return ((t_vector) {perl, perl, perl});
}

t_vector			rt_perlin_wood(float u, float v, t_texture text)
{
	double		n;
	double		ft;
	double		f;
	t_vector	c[2];

	(void)text;
	c[0] = (t_vector) {0.8, 0.6, 0.25};
	c[1] = (t_vector) {0.34, 0.176, 0.035};
	n = 20 * rt_perlin2d(u, v, text.pfrequ, text.pdepth);
	n -= floor(n);
	ft = n * M_PI;
	f = (1 - cos(ft)) / 2;
	return (ft_vadd(ft_vmul(c[0], 1 - f), ft_vmul(c[1], f)));
}

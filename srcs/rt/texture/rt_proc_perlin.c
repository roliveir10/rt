/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_proc_perlin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoussa <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/04 15:56:28 by mmoussa           #+#    #+#             */
/*   Updated: 2019/07/04 15:56:30 by mmoussa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include <math.h>

t_vector			rt_perlin_marble(float u, float v, t_texture text)
{
	double		perl;

	(void)text;
	perl = 1 - sqrt(fabs(cos(2 * M_PI *
		rt_perlin2d(u, v, 5, 4/*text->freq, text->depth*/))));
	return ((t_vector) {1 - perl, 1 - perl, 1 - perl});
}

t_vector			rt_perlin_lava(float u, float v, t_texture text)
{
	double		perl;

	(void)text;
	perl = 1 - sqrt(fabs(2 * M_PI *
		rt_perlin2d(u, v, 10, 1/*text->freq, text->depth*/)));
	return ((t_vector) {0.1 * perl, perl, perl});
}

t_vector			rt_perlin_sand(float u, float v, t_texture text)
{
	double		perl;

	(void)text;
	perl = rt_perlin2d(u, v, 1, 4/*text->freq, text->depth*/);
	return ((t_vector) {perl, perl, perl});
}

t_vector			rt_perlin_wood(float u, float v, t_texture text)
{
	double		perl;
	double		value;
	t_vector	c1;
	t_vector	c2;
	t_vector	color;

	(void)text;
	c1 = (t_vector) {1.0, 0.99, 0.98};
	c2 = (t_vector) {0.2, 0.12, 0.02};
	value = fmod(rt_perlin2d(u, v, 5, 4), 0.1);
	if (value > 0.05)
		value = 0.1 - value;
	perl = (1 - cos(M_PI * value / (0.05))) / 2;
	color.x = (c1.x * (1 - perl) + c2.x * perl);
	color.y = (c1.y * (1 - perl) + c2.y * perl);
	color.z = (c1.z * (1 - perl) + c2.z * perl);
	return (color);
}

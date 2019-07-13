/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_bump.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoussa <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/09 13:14:12 by mmoussa           #+#    #+#             */
/*   Updated: 2019/07/09 13:14:14 by mmoussa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include <math.h>

void			rt_bump_water(t_vector *bump, t_vector pos, t_form form)
{
	float		freq;
	t_vector	resize;

	resize = ft_vmul(pos, form.texture.bscale);
	freq = form.texture.bfrequ;
	bump->x = rt_noise3(resize.x - freq, resize.y, resize.z)
		- rt_noise3(resize.x + freq, resize.y, resize.z);
	bump->y = rt_noise3(resize.x, resize.y - freq, resize.z)
		- rt_noise3(resize.x, resize.y + freq, resize.z);
	bump->z = rt_noise3(resize.x, resize.y, resize.z - freq)
		- rt_noise3(resize.x, resize.y, resize.z + freq);
}

void			rt_bump_idk(t_vector *bump, t_vector pos, t_form form)
{
	float		freq;
	t_vector	resize;

	resize = ft_vmul(pos, form.texture.bscale);
	freq = form.texture.bfrequ;
	bump->x = sqrt(fabs(cos(2 * M_PI
		* rt_noise3(resize.x - freq, resize.y, resize.z)
		- rt_noise3(resize.x + freq, resize.y, resize.z))));
	bump->y = sqrt(fabs(cos(2 * M_PI
		* rt_noise3(resize.x, resize.y - freq, resize.z)
		- rt_noise3(resize.x, resize.y + freq, resize.z))));
	bump->z = sqrt(fabs(cos(2 * M_PI
		* rt_noise3(resize.x, resize.y, resize.z - freq)
		- rt_noise3(resize.x, resize.y, resize.z + freq))));
}

void			rt_bump_cos(t_vector *bump, t_vector pos, t_form form)
{
	float		freq;
	t_vector	resize;

	resize = ft_vmul(pos, form.texture.bscale);
	freq = form.texture.bfrequ;
	bump->x = (1 + cos(resize.x + rt_noise3(resize.x - freq, resize.y, resize.z)
		- rt_noise3(resize.x + freq, resize.y, resize.z))) / 2;
	bump->y = (1 + cos(resize.x + rt_noise3(resize.x, resize.y - freq, resize.z)
		- rt_noise3(resize.x, resize.y + freq, resize.z))) / 2;
	bump->z = (1 + cos(resize.x + rt_noise3(resize.x, resize.y, resize.z - freq)
		- rt_noise3(resize.x, resize.y, resize.z + freq))) / 2;
}

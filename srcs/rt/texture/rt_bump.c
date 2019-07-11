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

void			rt_bump_mapping(t_vector *bump, t_vector pos)
{
	float		freq;
	t_vector	resize;

	resize = ft_vmul(pos, 1/*bump scale*/);
	freq = 0.1/*bump depth*/;
	bump->x = rt_noise3(resize.x - freq, resize.y, resize.z)
		- rt_noise3(resize.x + freq, resize.y, resize.z);
	bump->y = rt_noise3(resize.x, resize.y - freq, resize.z)
		- rt_noise3(resize.x, resize.y + freq, resize.z);
	bump->z = rt_noise3(resize.x, resize.y, resize.z - freq)
		- rt_noise3(resize.x, resize.y, resize.z + freq);
	// if (bump->x == 0)
	// 	printf("%f, %f\n", pos.x, pos.y);
}

// void			rt_bump_mapping2(t_vector *bump, t_vector pos)
// {
// 	float		freq;
// 	t_vector	resize;

// 	resize = ft_vmul(pos, 1/*bump scale*/);
// 	freq = 0.08/*bump depth*/;
// 	bump->x = sqrt(fabs(cos(2 * M_PI * rt_noise3(resize.x - freq, resize.y, resize.z)
// 		- rt_noise3(resize.x + freq, resize.y, resize.z))));
// 	bump->y = sqrt(fabs(cos(2 * M_PI * rt_noise3(resize.x, resize.y - freq, resize.z)
// 		- rt_noise3(resize.x, resize.y + freq, resize.z))));
// 	bump->z = sqrt(fabs(cos(2 * M_PI * rt_noise3(resize.x, resize.y, resize.z - freq)
// 		- rt_noise3(resize.x, resize.y, resize.z + freq))));
// }

// void			rt_bump_mapping3(t_vector *bump, t_vector pos)
// {
// 	float		freq;
// 	t_vector	resize;

// 	resize = ft_vmul(pos, 1/*bump scale*/);
// 	freq = 0.1/*bump depth*/;
// 	bump->x = cos(resize.x + rt_noise3(resize.x - freq, resize.y, resize.z)
// 		- rt_noise3(resize.x + freq, resize.y, resize.z));
// 	bump->y = cos(resize.x + rt_noise3(resize.x, resize.y - freq, resize.z)
// 		- rt_noise3(resize.x, resize.y + freq, resize.z));
// 	bump->z = cos(resize.x + rt_noise3(resize.x, resize.y, resize.z - freq)
// 		- rt_noise3(resize.x, resize.y, resize.z + freq));
// }
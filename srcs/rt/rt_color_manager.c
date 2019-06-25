/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_color_manager.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roliveir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/10 17:17:08 by roliveir          #+#    #+#             */
/*   Updated: 2019/06/24 13:08:42 by roliveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "rt.h"

void			rt_attribute_color(int color, t_vector *s_color)
{
	s_color->x = (double)(color >> 16 & 0xFF) / 255;
	s_color->y = (double)(color >> 8 & 0xFF) / 255;
	s_color->z = (double)(color & 0xFF) / 255;
}

t_vector		rt_get_color(t_lum lum, t_inter inter, t_material mat)
{
	t_vector	color;
	t_vector	ltot;
	double		attenuation;
	double		angle;

	angle = ft_dot(inter.norm, inter.lightdir);
	ft_bzero(&color, sizeof(t_vector));
	if (angle > -1e-2)
	{
		attenuation = rt_attenuation(lum, ft_vdist(lum.pos, inter.pos));
		ltot = ft_vadd(ft_vadd(
					rt_spec(lum.color, inter, mat, attenuation),
					rt_diffuse(lum.color, angle, mat, attenuation)),
					rt_ambient(lum.color, mat, attenuation));
		return (ft_vvmul(ltot, inter.color));
	}
	return (rt_ambient_only(lum, mat, inter));
}

t_vector		rt_ambient_only(t_lum lum, t_material mat, t_inter inter)
{
	return (ft_vvmul(rt_ambient(lum.color, mat, rt_attenuation(lum,
						ft_vdist(lum.pos, inter.pos))), inter.color));
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_color_manager.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roliveir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/10 17:17:08 by roliveir          #+#    #+#             */
/*   Updated: 2019/06/26 16:21:29 by roliveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "rt.h"

t_vector		rt_attribute_color(int color)
{
	t_vector	vcolor;

	vcolor.x = (double)(color >> 16 & 0xFF) / 255;
	vcolor.y = (double)(color >> 8 & 0xFF) / 255;
	vcolor.z = (double)(color & 0xFF) / 255;
	return (vcolor);
}

t_vector		rt_get_color(t_lum lum, t_inter inter, t_material mat)
{
	t_vector	color;
	t_vector	ltot;
	double		attenuation;
	double		s_atte;
	double		angle;

	angle = ft_dot(inter.norm, inter.lightdir);
	ft_bzero(&color, sizeof(t_vector));
	if (angle > 0)
	{
		attenuation = rt_attenuation(lum, ft_vdist(lum.pos, inter.pos));
		s_atte = 1;
		if (lum.type == LSPOT)
			s_atte = rt_spotlight(inter.pos, lum);
		ltot = ft_vadd(ft_vadd(
					rt_spec(lum.color, inter, mat, attenuation * s_atte),
					rt_diffuse(lum.color, angle, mat, attenuation * s_atte)),
					rt_ambient(lum.color, mat, attenuation));
		return (ft_vvmul(ltot, inter.color));
	}
	return (rt_ambient_only(lum, mat, inter));
}

t_vector		rt_ambient_only(t_lum lum, t_material mat, t_inter inter)
{
	double		attenuation;

	attenuation = rt_attenuation(lum, ft_vdist(lum.pos, inter.pos));
	return (ft_vvmul(rt_ambient(lum.color, mat, attenuation), inter.color));
}

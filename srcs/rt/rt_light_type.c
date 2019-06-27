/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_light_type.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roliveir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/26 12:46:44 by roliveir          #+#    #+#             */
/*   Updated: 2019/06/26 16:19:03 by roliveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "rt.h"

t_vector			rt_get_lightdir(t_vector o, t_lum lum)
{
	if (lum.type == LPOINT || lum.type == LSPOT)
		return (ft_get_vector(o, lum.pos));
	return (ft_vmul(lum.dir, -1));
}

#include <stdio.h>

double				rt_spotlight(t_vector pos, t_lum lum)
{
	double			theta;
	double			epsilon;

	if (lum.type == LSPOT)
	{
		lum.cutoff = cos(0.0 / 180.0 * M_PI);
		epsilon = lum.cutoff - cos(15.0 / 180.0 * M_PI);
		theta = ft_dot(rt_get_lightdir(pos, lum),
				ft_vmul(ft_normalize(lum.dir), -1));
		return (ft_clamp((theta - cos(15.0 / 180.0 * M_PI)) / epsilon, 0, 1));
	}
	return (1);
}

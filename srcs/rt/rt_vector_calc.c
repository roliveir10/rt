/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_vector_calc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roliveir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/08 10:42:05 by roliveir          #+#    #+#             */
/*   Updated: 2019/06/23 14:03:13 by roliveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "rt.h"

t_vector		rt_get_vecdir(t_cam cam, double x, double y)
{
	t_vector	dir;
	double		xindent;
	double		yindent;

	xindent = cam.vp_width / (double)SCREENX;
	yindent = cam.vp_height / (double)SCREENY;
	dir = ft_vsub(ft_vmul(cam.vec_dir[1], yindent * y),
		ft_vadd(cam.vp_upleft, ft_vmul(cam.vec_dir[0], xindent * x)));
	return (ft_normalize(dir));
}

t_vector		rt_get_posinter(t_ray ray, double dist)
{
	return (ft_vadd(ray.o, ft_vmul(ray.dir, dist)));
}

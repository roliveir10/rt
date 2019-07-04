/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_medium_shapes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutrol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/02 15:31:15 by oboutrol          #+#    #+#             */
/*   Updated: 2019/07/04 14:09:00 by oboutrol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "rt.h"

#include <stdio.h>
double			rt_torus(t_ray ray, t_form form)
{
	double		vect[5];
	double		coeff[6];
	double		rs;
	double		res;

	rs = form.r * form.r;
	coeff[0] = 4 * rs * (ray.dir.x * ray.dir.x + ray.dir.y * ray.dir.y);
	coeff[1] = 8 * rs * (ray.o.x * ray.dir.x + ray.o.y * ray.dir.y);
	coeff[2] = 4 * rs * (ray.o.x * ray.o.x + ray.o.y * ray.o.y);
	coeff[3] = ray.dir.x * ray.dir.x + ray.dir.y * ray.dir.y
		+ ray.dir.z * ray.dir.z;
	coeff[4] = 2 * (ray.o.x * ray.dir.x + ray.dir.y * ray.o.y
			+ ray.o.z * ray.dir.z);
	coeff[5] = ray.o.x * ray.o.x + ray.o.y * ray.o.y
		+ ray.o.z * ray.o.z + rs - form.angle * form.angle;
	vect[0] = coeff[3] * coeff[3];
	vect[1] = 2 * coeff[3] * coeff[4];
	vect[2] = 2 * coeff[3] * coeff[5] + coeff[4] * coeff[4] - coeff[0];
	vect[3] = 2 * coeff[4] * coeff[5] - coeff[1];
	vect[4] = coeff[5] * coeff[5] - coeff[2];
	res = ft_4th_degree(vect);
//	printf("vect: %f %f %f %f %f\n", vect[0], vect[1], vect[2], vect[3],
//			vect[4]);
//	printf("res: %f\n", res);
	return (res);
}

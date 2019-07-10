/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_medium_shapes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutrol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/02 15:31:15 by oboutrol          #+#    #+#             */
/*   Updated: 2019/07/06 13:43:27 by oboutrol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "rt.h"

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
	return (res);
}

double			rt_hyperbol(t_ray ray, t_form form)
{
	double		a;
	double		b;
	double		c;
	double		coeff[3];

	coeff[0] = 1 / form.direct.x / form.direct.x;
	coeff[1] = 1 / form.direct.y / form.direct.y;
	coeff[2] = 1 / form.direct.z / form.direct.z;
	a = ray.dir.x * ray.dir.x * coeff[0]
		+ ray.dir.y * ray.dir.y * coeff[1]
		- ray.dir.z * ray.dir.z * coeff[2];
	b = 2 * ray.dir.x * ray.o.x * coeff[0]
		+ 2 * ray.dir.y * ray.o.y * coeff[1]
		- 2 * ray.dir.z * ray.o.z * coeff[2];
	c = ray.o.x * ray.o.x * coeff[0]
		+ ray.o.y * ray.o.y * coeff[1]
		- ray.o.z * ray.o.z * coeff[2] - form.r;
	return (ft_2nd_degree(a, b, c));
}

double			rt_cubet(t_ray ray, t_form form)
{
	double		vect[5];
	double		res;

	(void)form;
	vect[0] = pow(ray.dir.x, 4) + pow(ray.dir.y, 4) + pow(ray.dir.z, 4);
	vect[1] = 4 * (pow(ray.dir.x, 3) * ray.o.x + pow(ray.dir.y, 3) * ray.o.y
			+ pow(ray.dir.z, 3) * ray.o.z);
	vect[2] = 6 * (ray.dir.x * ray.dir.x * ray.o.x * ray.o.x
			+ ray.dir.y * ray.dir.y * ray.o.y * ray.o.y
			+ ray.dir.z * ray.dir.z * ray.o.z * ray.o.z)
	   - 5 * (ray.dir.x * ray.dir.x + ray.dir.y * ray.dir.y
			+ ray.dir.z * ray.dir.z);
	vect[3] = 4 * (pow(ray.o.x, 3) * ray.dir.x + pow(ray.o.y, 3) * ray.dir.y
			+ pow(ray.o.z, 3) * ray.dir.z) - 10 * (ray.dir.x * ray.o.x
			+ ray.dir.y * ray.o.y + ray.dir.z * ray.o.z);
	vect[4] = pow(ray.o.x, 4) + pow(ray.o.y, 4) + pow(ray.o.z, 4)
		- 5 * (ray.o.x * ray.o.x + ray.o.y * ray.o.y + ray.o.z * ray.o.z)
		+ 11.8;
	res = ft_4th_degree(vect);
	return (res);
}

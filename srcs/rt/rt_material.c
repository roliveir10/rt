/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_material.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roliveir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/19 01:26:51 by roliveir          #+#    #+#             */
/*   Updated: 2019/06/26 08:22:42 by oboutrol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void				rt_attr_material(t_vector *v, double a, double b,
		double c)
{
	v->x = a;
	v->y = b;
	v->z = c;
}

static t_material		rt_mat_nothing(t_scene scene)
{
	t_material			mat;

	rt_attr_material(&mat.ambient, scene.ambient, scene.ambient, scene.ambient);
	rt_attr_material(&mat.diffuse, 0.5, 0.5, 0.5);
	rt_attr_material(&mat.specular, scene.spec, scene.spec, scene.spec);
	mat.shininess = 1;
	return (mat);
}

static t_material		rt_mat_all(t_ematerial emat)
{
	t_material			mat;
	double				buff[3];

	rt_material_ambient(buff, emat);
	rt_attr_material(&mat.ambient, buff[0], buff[1], buff[2]);
	rt_material_diffuse(buff, emat);
	rt_attr_material(&mat.diffuse, buff[0], buff[1], buff[2]);
	rt_material_specular(buff, emat);
	rt_attr_material(&mat.specular, buff[0], buff[1], buff[2]);
	mat.shininess = rt_material_shininess(emat);
	return (mat);
}

t_material				rt_get_material(t_ematerial emat, t_scene scene)
{
	if (emat == NOTHING)
		return (rt_mat_nothing(scene));
	else
		return (rt_mat_all(emat - 1));
}

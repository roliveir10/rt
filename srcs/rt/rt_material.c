/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_material.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roliveir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/19 01:26:51 by roliveir          #+#    #+#             */
/*   Updated: 2019/06/23 18:48:21 by oboutrol         ###   ########.fr       */
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

static t_material		rt_mat_jade(t_scene scene)
{
	t_material			mat;

	(void)scene;
	rt_attr_material(&mat.ambient, 0.135, 0.2225, 0.1575);
	rt_attr_material(&mat.diffuse, 0.54, 0.89, 0.63);
	rt_attr_material(&mat.specular, 0.316228, 0.316228, 0.316228);
	mat.shininess = 0.1;
	return (mat);
}

t_material				rt_get_material(t_ematerial emat, t_scene scene)
{
	static int			mat_tab[NBR_MATERIAL] = {NOTHING, JADE};
	static t_material	(*func[NBR_MATERIAL])(t_scene) = {
		rt_mat_nothing, rt_mat_jade};
	int					i;

	i = -1;
	while (++i < NBR_MATERIAL)
		if (emat == mat_tab[i])
			return (func[i](scene));
	return (func[0](scene));
}

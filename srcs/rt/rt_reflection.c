/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_reflection.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roliveir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/27 10:30:06 by roliveir          #+#    #+#             */
/*   Updated: 2019/06/28 11:00:33 by roliveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "rt.h"

t_vector			rt_reflection(t_env *env, t_inter inter, int depth)
{
	double			i;
	t_ray			ray;

	i = env->form[inter.id].iref;
	if (i > 0 && depth < DEPTH_MAX)
	{
		ray.o = inter.pos;
		ray.dir = inter.refdir;
		return ((ft_vadd(ft_vmul(rt_viewdir_inter(env, ray, depth + 1), i),
						rt_light_manager(env, inter))));
	}
	return (rt_light_manager(env, inter));
}

t_vector			rt_refraction(t_env *env, t_inter inter, int depth)
{
	double			indice;
	t_ray			ray;

	indice = 1;
	if (env->form[inter.id].ftype == SPHERE && depth > DEPTH_MAX)
	{
		ray.o = inter.pos;
		ray.dir = inter.refrdir;
		return ((ft_vadd(ft_vmul(rt_viewdir_inter(env, ray, depth + 1), indice),
						rt_light_manager(env, inter))));
	}
	return (rt_light_manager(env, inter));
}

t_vector			rt_get_refdir(t_vector normal, t_vector dir)
{
	return (ft_vsub(ft_vmul(normal, 2 * ft_dot(normal, dir)), dir));
}

t_vector			rt_get_refrdir(double n1, double n2, t_inter inter)
{
	double			n;
	double			c1;
	double			c2;

	n = n1 / n2;
	c1 = ft_dot(inter.norm, inter.refdir);
	c2 = sqrt(1 - pow(n, 2) * (1 - pow(c1, 2)));
	return (ft_vadd(ft_vmul(inter.refdir, n),
				ft_vmul(inter.norm, n * c1 - c2)));
}

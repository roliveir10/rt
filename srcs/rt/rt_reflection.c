/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_reflection.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roliveir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/27 10:30:06 by roliveir          #+#    #+#             */
/*   Updated: 2019/06/29 05:04:11 by roliveir         ###   ########.fr       */
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
	t_ray			ray;
	t_vector		light;
	double			tpy;

	light = rt_light_manager(env, inter);
	if (env->form[inter.id].ftype == SPHERE && depth < DEPTH_MAX)
	{
		tpy = env->form[inter.id].itpy;
		ray.o = ft_vsub(ft_vmul(inter.norm, 2e-5), inter.pos);
		ray.dir = inter.refrdir;
		return ((ft_vadd(ft_vmul(rt_viewdir_inter(env, ray, depth + 1), tpy),
						light)));
	}
	return (rt_light_manager(env, inter));
}

t_vector			rt_get_refdir(t_vector normal, t_vector dir, double ndoti)
{
	return (ft_vsub(ft_vmul(normal, 2 * ndoti), dir));
}

t_vector			rt_get_refrdir(double n2, t_inter inter, double c1,
		t_vector vdir)
{
	double			n;
	double			c2;
	t_vector		refr;

	ft_bzero(&refr, sizeof(t_vector));
	n = c1 > 0 ? n2 : 1 / n2;
	c1 = c1 > 0 ? c1 : -c1;
	c2 = 1.0 - pow(n, 2.0) * (1.0 - pow(c1, 2.0));
	if (c2 < 0)
		return (refr);
	return (ft_vadd(ft_vmul(vdir, n),
				ft_vmul(inter.norm, n * c1 - sqrt(c2))));
}

double				rt_fresnel(double ndoti, t_inter inter, double n2)
{
	double			n1;
	double			tmp;
	double			sint;

	(void)inter;
	n1 = 1;
	if (ndoti > 0)
	{
		tmp = n1;
		n1 = n2;
		n2 = tmp;
	}
	sint = n1 / n2 * sqrt(1 - pow(ndoti, 2));
	if (sint >= 1)
		return (1);
	else
	{
		double cost = sqrt(1 - pow(sint, 2));
		ndoti = fabs(ndoti);
		double Rs = ((n2 * ndoti) - (n1 * cost)) / ((n2 * ndoti) + (n1 * cost));
		double Rp = ((n1 * ndoti) - (n2 * cost)) / ((n1 * ndoti) + (n2 * cost));
		return ((pow(Rs, 2) + pow(Rp, 2)) / 2.0);
	}

}

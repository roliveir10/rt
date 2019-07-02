/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_inter_manager.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roliveir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/09 11:28:08 by roliveir          #+#    #+#             */
/*   Updated: 2019/06/29 05:04:08 by roliveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static t_vector		rt_no_inter(void)
{
	t_vector		color_black;
	t_vector		color_sky;

	ft_bzero(&color_black, sizeof(t_vector));
	color_sky.x = 135.0 / 255.0;
	color_sky.y = 206.0 / 255.0;
	color_sky.z = 235.0 / 255.0;
	return (color_sky);
}

double				rt_inter(t_ftype ftype, t_ray *ray, t_form form)
{
	static double	(*func[NBR_FORM])(t_ray, t_form) = {
		rt_sphere, rt_plan, rt_cylindre, rt_cone};

	rt_set_ref(ray, form);
	return (func[ftype](*ray, form));
}

static void			rt_getinter_data(t_env *env, t_inter *inter, t_vector vdir)
{
	int				i;
	double			ndoti;

	i = 3;
	inter->color = env->form[inter->id].color;
	inter->norm = rt_get_normal(inter->pos, env->form[inter->id]);
	rt_reset_point(env->form[inter->id], &inter->pos);
	while (--i + 1)
		inter->norm = ft_vrotate(inter->norm, env->form[inter->id].mati[i]);
	ndoti = ft_dot(inter->norm, vdir);
	if (ndoti > 0)
		inter->norm = ft_vmul(inter->norm, -1);
	inter->pos = ft_vadd(ft_vmul(inter->norm, 1e-5), inter->pos);
	inter->viewdir = ft_vmul(vdir, -1);
	inter->blinn = env->scene.blinn;
	if (env->form[inter->id].iref > 0)
	{
		inter->refdir = rt_get_refdir(inter->norm, vdir, ndoti);
		inter->kr = rt_fresnel(ndoti, *inter, 1);
	}
//	if (env->form[inter->id].transparency > 0)
	if (env->form[inter->id].ftype == SPHERE)
	{
		if (inter->kr < 1)
			inter->refrdir = rt_get_refrdir(1, *inter, ndoti, vdir);
	}
}

static int			rt_shape_inter(t_env *env, int *indsh, t_ray *ray,
		double *min)
{
	double			dist;

	dist = rt_inter(env->form[*indsh].ftype, ray, env->form[*indsh]);
	if (dist > 0 && (dist < *min || *min == -1.0))
	{
		*min = dist;
		return (1);
	}
	return (0);
}
// case if only reflection

double				rt_first_inter(t_env *env, t_ray ray_o,
	t_inter *inter)
{
	int			i;
	double			min;
	t_ray			ray;

	i = -1;
	min = -1.0;
	while (++i < env->nbr_form)
	{
		ray = ray_o;
		if (rt_shape_inter(env, &i, &ray, &min))
		{
			inter->id = i;
			inter->pos = rt_get_posinter(ray, min);
		}
	}
	return (min);
}

t_vector			rt_viewdir_inter(t_env *env, t_ray ray_orig, int depth)
{
	t_inter			inter;
	t_vector		color;
	t_vector		refl_color;
	t_vector		refr_color;

	ft_bzero(&inter, sizeof(t_inter));
	ft_bzero(&color, sizeof(t_vector));
	if (rt_first_inter(env, ray_orig, &inter)  < 0)
		return (ft_vadd(color, rt_no_inter()));
	rt_getinter_data(env, &inter, ray_orig.dir);
	if (env->form[inter.id].ftype == SPHERE && inter.kr < 1)
	{
		refr_color = rt_refraction(env, inter, depth);
		refl_color = rt_reflection(env, inter, depth);
		return (ft_vadd(color, ft_vadd(ft_vmul(refr_color, 1.0 - inter.kr),
				ft_vmul(refl_color, inter.kr))));
	}
	refl_color = rt_reflection(env, inter, depth);
	return (ft_vadd(color, refl_color));
}

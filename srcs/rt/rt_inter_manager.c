/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_inter_manager.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roliveir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/09 11:28:08 by roliveir          #+#    #+#             */
/*   Updated: 2019/06/24 13:07:59 by roliveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static t_vector		rt_no_inter(void)
{
	t_vector		color_black;

	ft_bzero(&color_black, sizeof(t_vector));
	return (color_black);
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

	i = 3;
	inter->color = env->form[inter->id].color;
	inter->norm = rt_get_normal(inter->pos, env->form[inter->id]);
	rt_reset_point(env->form[inter->id], &inter->pos);
	while (--i + 1)
		inter->norm = ft_vrotate(inter->norm, env->form[inter->id].mati[i]);
	if (ft_dot(inter->norm, vdir) > 0)
		inter->norm = ft_vmul(inter->norm, -1);
	inter->pos = ft_vadd(ft_vmul(inter->norm, 1e-5), inter->pos);
	inter->viewdir = ft_vmul(vdir, -1);
	inter->blinn = env->scene.blinn;
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

t_vector			rt_viewdir_inter(t_env *env, t_ray ray_orig)
{
	int				i;
	t_ray			ray;
	t_inter			inter;
	double			min;

	i = -1;
	min = -1.0;
	ft_bzero(&inter, sizeof(t_inter));
	while (++i < env->nbr_form)
	{
		ray = ray_orig;
		if (rt_shape_inter(env, &i, &ray, &min))
		{
			inter.id = i;
			inter.pos = rt_get_posinter(ray, min);
		}
	}
	if (min < 0)
		return (rt_no_inter());
	rt_getinter_data(env, &inter, ray_orig.dir);
	return (rt_light_manager(env, inter));
}

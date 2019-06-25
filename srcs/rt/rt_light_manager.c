/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_light_manager.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roliveir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/09 21:28:14 by roliveir          #+#    #+#             */
/*   Updated: 2019/06/24 12:58:49 by roliveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "rt.h"

static t_vector		rt_nolight_inter(t_lum lum, t_inter *inter, t_material m)
{
	if (lum.type == LCAST)
		inter->lightdir = lum.pos;
	else
		inter->lightdir = ft_get_vector(inter->pos, lum.pos);
	return (rt_get_color(lum, *inter, m));
}

static t_vector		rt_light_tocolor(t_env *env, int indsh, int indli,
		t_inter *inter)
{
	t_vector		color;

	if (indsh == env->nbr_form)
		color = rt_nolight_inter(env->lum[indli], inter,
				env->form[inter->id].material);
	else
		color = rt_ambient_only(env->lum[indli],
				env->form[inter->id].material, *inter);
	return (color);
}

static int			rt_light_inter(t_env *env, int indsh, t_ray *ray, int indli)
{
	double			dist;

	dist = rt_inter(env->form[indsh].ftype, ray, env->form[indsh]);
	if (dist > 0)
	{
		rt_reset_point(env->form[indsh], &ray->o);
		if (dist < ft_vdist(env->lum[indli].pos, ray->o))
			return (1);
	}
	return (0);
}

t_vector			rt_light_manager(t_env *env, t_inter inter)
{
	int				i;
	int				j;
	t_ray			ray;
	t_vector		color;

	i = -1;
	ft_bzero(&color, sizeof(t_vector));
	while (++i < env->nbr_lum)
	{
		j = -1;
		while (++j < env->nbr_form)
		{
			ray.o = inter.pos;
			ray.dir = ft_get_vector(ray.o, env->lum[i].pos);
			if (rt_light_inter(env, j, &ray, i))
				break ;
		}
		color = ft_vadd(rt_light_tocolor(env, j, i, &inter), color);
	}
	return (color);
}

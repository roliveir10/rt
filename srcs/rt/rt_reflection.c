/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_reflection.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roliveir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/27 10:30:06 by roliveir          #+#    #+#             */
/*   Updated: 2019/06/27 13:36:53 by roliveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_vector			rt_reflection(t_env *env, t_inter inter, t_ray ray,
		int depth)
{
	double			i;

	i = env->form[inter.id].ireflec;
	if (i > 0 && depth < DEPTH_MAX)
	{
		ray.o = inter.pos;
		ray.dir = ft_vsub(ft_vmul(inter.norm, 2 * ft_dot(inter.norm, ray.dir)),
				ray.dir);
		return ((ft_vadd(ft_vmul(rt_viewdir_inter(env, ray, depth + 1), i),
					rt_light_manager(env, inter))));
	}
	return (rt_light_manager(env, inter));
}

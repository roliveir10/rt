/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_texture_perlin.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoussa <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/01 14:06:56 by mmoussa           #+#    #+#             */
/*   Updated: 2019/07/01 14:06:58 by mmoussa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <fcntl.h>
#include "mlx.h"
#include "rt.h"

t_vector			rt_perlinval(float u, float v, t_texture text)
{
	// if (text.perlin == PMARBLE)
		return (rt_perlin_marble(u, v, text));
	// else if (text.perlin == PLAVA)
	//	 return (rt_perlin_lava(u, v, text));
	// else if (text.perlin == PSAND)
	//	 return (rt_perlin_sand(u, v, text));
	// else if (text.perlin == PWOOD)
	//	 return (rt_perlin_wood(u, v, text));
	return ((t_vector) {1, 1, 1});
}

t_vector			rt_perlin_sphere(t_vector normal, t_vector intercolor,
		t_inter *inter, t_env *env)
{
	float		u;
	float		v;
	int			i;

	i = 3;
	while (--i + 1)
		normal = ft_vrotate(normal, env->form[inter->id].mat[i]);
	u = 0.5 + atan2(normal.z, normal.x) / M_PI * 0.5;
	v = 0.5 - asin(normal.y) / M_PI;
	intercolor = rt_perlinval(u, v, env->form[inter->id].texture);
	return (intercolor);
}

t_vector			rt_perlin_plan(t_vector normal, t_vector intercolor,
		t_inter *inter, t_env *env)
{
	t_vector		uv_axis[2];
	double			uv_coord[2];
	int				i;

	i = 3;
	while (--i + 1)
		uv_axis[0] = ft_vrotate(ft_normalize((t_vector) {normal.y,
			normal.x, 0}), env->form[inter->id].mat[i]);
	uv_axis[1] = ft_cross(normal, uv_axis[0]);
	uv_coord[0] = ft_dot(uv_axis[0], inter->pos)
		/ env->form[inter->id].texture.scale;
	uv_coord[1] = ft_dot(uv_axis[1], inter->pos)
		/ env->form[inter->id].texture.scale;
	intercolor = rt_perlinval(uv_coord[0], uv_coord[1],
		env->form[inter->id].texture);
	return (intercolor);
}

t_vector			rt_perlin_cylindre(t_vector normal, t_vector intercolor,
		t_inter *inter, t_env *env)
{
	t_vector	d;
	float		u;
	float		v;
	int			i;

	(void)normal;
	i = 3;
	d = ft_vsub(inter->pos, env->form[inter->id].center);
	while (--i + 1)
		d = ft_vrotate(d, env->form[inter->id].mat[i]);
	u = 0.5 + atan2(d.z, d.x) / M_PI * 0.5;
	v = d.y / env->form[inter->id].texture.scale;
	intercolor = rt_perlinval(u, v, env->form[inter->id].texture);
	return (intercolor);
}

t_vector			rt_tperlin(t_vector normal, t_vector intercolor, t_env *env,
						t_inter *inter)
{
	static int		tftype[NBR_FORM] = {SPHERE, PLAN, CYLINDRE, CONE};
	static t_vector	(*func[NBR_FORM])(t_vector, t_vector, t_inter*,
		t_env*) = {rt_perlin_sphere, rt_perlin_plan,
		rt_perlin_cylindre, rt_perlin_cylindre};
	int				i;

	i = -1;
	while (++i < NBR_FORM)
		if (env->form[inter->id].ftype == tftype[i])
			intercolor = func[i](normal, intercolor, inter, env);
	return (intercolor);
}

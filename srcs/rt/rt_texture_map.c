/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_texture_map.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoussa <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/26 18:02:56 by mmoussa           #+#    #+#             */
/*   Updated: 2019/06/26 18:02:59 by mmoussa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <fcntl.h>
#include "mlx.h"
#include "rt.h"

t_vector			rt_getcolor(t_timage img, int x, int y)
{
	int		color;
	int		c;

	c = (y * img.width + x) * 4;
	color = img.buffer_ptr[c];
	if (color == -120 && img.buffer_ptr[c + 1] == 0
		&& img.buffer_ptr[c + 2] == -104)
		return ((t_vector) {1, 1, 1});
	color += img.buffer_ptr[c + 1] * 256;
	color += img.buffer_ptr[c + 2] * 256 * 256;
	return (rt_attribute_color(color));
}

t_vector			rt_map_sphere(t_vector normal, t_vector intercolor,
		t_inter *inter, t_env *env)
{
	float		u;
	float		v;
	int			i;

	i = 3;
	while (--i + 1)
		normal = ft_vrotate(normal, env->form[inter->id].mat[i]);
	u = 0.5 + atan2(normal.z, normal.x) / M_PI * 0.5;
	v = 0.5 - asin(-normal.y) / M_PI;
	u = ft_clamp(u * env->form[inter->id].timage.width, 0,
		env->form[inter->id].timage.width - 1);
	v = ft_clamp(v * env->form[inter->id].timage.height, 0,
		env->form[inter->id].timage.height - 1);
	intercolor = rt_getcolor(env->form[inter->id].timage, (int)u, (int)v);
	return (intercolor);
}

t_vector			rt_map_plan(t_vector normal, t_vector intercolor,
		t_inter *inter, t_env *env)
{
	t_vector		u_axis;
	t_vector		v_axis;
	double			u_coord;
	double			v_coord;
	int				i;

	i = 3;
	while (--i + 1)
		u_axis = ft_vrotate(ft_normalize((t_vector) {normal.y, normal.x, 0}),
			env->form[inter->id].mat[i]);
	v_axis = ft_cross(normal, u_axis);
	u_coord = ft_dot(u_axis, inter->pos) / env->form[inter->id].texture.scale;
	v_coord = ft_dot(v_axis, inter->pos) / env->form[inter->id].texture.scale;
	u_coord -= floor(u_coord);
	v_coord -= floor(v_coord);
	intercolor = rt_getcolor(env->form[inter->id].timage, (int)(fabs(u_coord)
		* (env->form[inter->id].timage.width - 1)), (int)(fabs(v_coord)
		* (env->form[inter->id].timage.height - 1)));
	return (intercolor);
}

t_vector			rt_map_cylindre(t_vector normal, t_vector intercolor,
		t_inter *inter, t_env *env)
{
	t_vector	d;
	float		u;
	float		v;

	(void)normal;
	d = ft_vsub(inter->pos, ft_vvmul(env->form[inter->id].center,
		env->form[inter->id].rotation));
	u = 0.5 + atan2(d.z, d.x) / M_PI * 0.5;
	v = d.y / env->form[inter->id].texture.scale;
	v -= floor(v);
	u = ft_clamp(u * env->form[inter->id].timage.width, 0,
		env->form[inter->id].timage.width - 1);
	v = ft_clamp(v * env->form[inter->id].timage.height, 0,
		env->form[inter->id].timage.height - 1);
	intercolor = rt_getcolor(env->form[inter->id].timage, (int)u, (int)v);
	return (intercolor);
}

t_vector			rt_tmap(t_vector normal, t_vector intercolor, t_env *env,
						t_inter *inter)
{
	static int		tftype[NBR_FORM] = {SPHERE, PLAN, CYLINDRE, CONE};
	static t_vector	(*func[NBR_FORM])(t_vector, t_vector, t_inter*,
		t_env*) = {rt_map_sphere, rt_map_plan,
		rt_map_cylindre, rt_map_cylindre};
	int				i;

	i = -1;
	while (++i < NBR_FORM)
		if (env->form[inter->id].ftype == tftype[i])
			intercolor = func[i](normal, intercolor, inter, env);
	return (intercolor);
}

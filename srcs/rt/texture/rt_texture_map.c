/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_texture_map.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoussa <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/26 18:02:56 by mmoussa           #+#    #+#             */
/*   Updated: 2019/07/11 18:05:17 by oboutrol         ###   ########.fr       */
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
	v = 0.5 - asin(normal.y) / M_PI;
	u = (int)(u * env->form[inter->id].timage.width
		+ env->form[inter->id].texture.offsetx)
		% env->form[inter->id].timage.width;
	v = (int)(v * env->form[inter->id].timage.height
		+ env->form[inter->id].texture.offsety)
		% env->form[inter->id].timage.height;
	intercolor = rt_getcolor(env->form[inter->id].timage, (int)u, (int)v);
	return (intercolor);
}

t_vector			rt_map_plan(t_vector normal, t_vector intercolor,
		t_inter *inter, t_env *env)
{
	t_vector		uv_axis[2];
	double			uv_coord[2];
	double			imagex;
	double			imagey;
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
	uv_coord[0] -= floor(uv_coord[0]);
	uv_coord[1] -= floor(uv_coord[1]);
	imagex = (int)(fabs(uv_coord[0]) * (env->form[inter->id].timage.width
		- 1) + env->form[inter->id].texture.offsetx)
		% env->form[inter->id].timage.width;
	imagey = (int)(fabs(uv_coord[1]) * (env->form[inter->id].timage.height
		- 1) + env->form[inter->id].texture.offsety)
		% env->form[inter->id].timage.height;
	intercolor = rt_getcolor(env->form[inter->id].timage, imagex, imagey);
	return (intercolor);
}

t_vector			rt_map_cylindre(t_vector normal, t_vector intercolor,
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
	v -= floor(v);
	u = (int)(u * env->form[inter->id].timage.width
		+ env->form[inter->id].texture.offsetx)
		% (env->form[inter->id].timage.width - 1);
	v = (int)(v * env->form[inter->id].timage.height
		+ env->form[inter->id].texture.offsetx)
		% (env->form[inter->id].timage.height - 1);
	intercolor = rt_getcolor(env->form[inter->id].timage, (int)u, (int)v);
	return (intercolor);
}

t_vector			rt_tmap(t_vector normal, t_vector intercolor, t_env *env,
						t_inter *inter)
{
	static int		tftype[NBR_FORM_TEXT] = {SPHERE, PLAN, CYLINDRE, CONE};
	static t_vector	(*func[NBR_FORM_TEXT])(t_vector, t_vector, t_inter*,
		t_env*) = {rt_map_sphere, rt_map_plan,
		rt_map_cylindre, rt_map_cylindre};
	int				i;

	i = -1;
	while (++i < NBR_FORM_TEXT)
		if (env->form[inter->id].ftype == tftype[i])
			intercolor = func[i](normal, intercolor, inter, env);
	return (intercolor);
}

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
#include <unistd.h>

/*
** TEXTURE LOAD AND GET COLOR PIXEL
*/

// t_vector		rt_getcolor(t_timage img, int x, int y)
// {
// 	int	color;
// 	int	c;
	
	
// 	// x = (x * SCALE + DecalageX)  % img.width;
// 	// y = (y  * SCALE + DecalageY)  % img.width;
// 	x = (ft_abs(x) + img.width / 2) % (img.width);
// 	y = (ft_abs(y) + img.height / 2) % (img.height);
// 	if (y > img.height)
// 	{
// 		printf("x = %d | y = %d\n", img.height, y);
// 		// return ((t_vector) {0, 1, 0});
// 	}
// 	c = (y * img.width + x) * 4;
// 	color = img.buffer_ptr[c];
// 	if (color == -120 && img.buffer_ptr[c + 1] == 0 && img.buffer_ptr[c + 2] == -104)
// 		return ((t_vector) {1, 1, 1});
// 	color += img.buffer_ptr[c + 1] * 256;
// 	color += img.buffer_ptr[c + 2] * 256 * 256;
// 	return (rt_attribute_color(color));
// }

t_vector		rt_getcolor(t_timage img, float x, float y)
{
	int	color;
	int	c;
	
	x = ft_clamp(floor(x * img.width - 0.5), 0, img.width - 2);
	y = ft_clamp(floor(y * img.height - 0.5), 0, img.height - 2);
	// x = (x * SCALE + DecalageX)  % img.width;
	// y = (y  * SCALE + DecalageY)  % img.width;
	// x = (ft_abs(x) + img.width / 2) % (img.width);
	// y = (ft_abs(y) + img.height / 2) % (img.height);
	c = (y * img.width + x) * 4;
	color = img.buffer_ptr[c];
	if (color == -120 && img.buffer_ptr[c + 1] == 0 && img.buffer_ptr[c + 2] == -104)
		return ((t_vector) {1, 1, 1});
	color += img.buffer_ptr[c + 1] * 256;
	color += img.buffer_ptr[c + 2] * 256 * 256;
	return (rt_attribute_color(color));
}

/*
** END LOAD / GET
*/

t_vector		rt_map_sphere(t_vector normal, t_vector intercolor,
		t_inter *inter, t_env *env)
{
	// double		o;
	// double		p;
	// double		a;

	// (void)inter;
	// a = 1 - env->form[inter->id].texture.atexture;
	// p = acos(-1 * ft_dot(normal, (t_vector) {0, 1, 0}))
	// 	/ M_PI * env->form[inter->id].texture.recurrence;
	// o = atan2(ft_dot(normal, (t_vector) {0, 0, 1}), ft_dot(normal,
	// 	(t_vector) {1, 0, 0})) / M_PI * env->form[inter->id].texture.recurrence;
	// if (o < 0)
	// 	o = fabs(o - 1);
	// if (((int)p % 2 == 0 && (int)o % 2 == 0) ||
	// 	(((int)p + 1) % 2 == 0 && ((int)o + 1) % 2 == 0))
	// {
	// 	intercolor = ft_vsub(env->form[inter->id].texture.color,
	// 		(t_vector) {1, 1, 1});
	// 	intercolor = ft_vmul(intercolor, -a);
	// }
	// else
	// 	intercolor = ft_vmul(intercolor, a);
	// return (intercolor);
	t_vector	axis[2];
	double		uv[3];
	double		a;

	a = 1 - env->form[inter->id].texture.atexture;
	axis[0] = (t_vector) {normal.y, normal.z, -normal.x};
	axis[1] = ft_cross(axis[0], normal);
	uv[0] = cos(ft_dot(inter->pos, axis[0]));
	uv[1] = cos(ft_dot(inter->pos, axis[1]));
	uv[2] = cos(ft_dot(inter->pos, normal));
	// printf("%f, %f, %f\n", uv[0], uv[1], uv[2]);
	intercolor = rt_getcolor(env->form[inter->id].timage, ft_abs((int)inter->pos.x), ft_abs((int)inter->pos.y)/*uv[0] + 1.0, uv[1] + 1.0*/);
	// printf("%f, %f, %f\n", intercolor.x, intercolor.y, intercolor.z);
	return (intercolor);
}

t_vector		rt_map_plan(t_vector normal, t_vector intercolor,
		t_inter *inter, t_env *env)
{
	// (void)normal;
	// intercolor = rt_getcolor(env->form[inter->id].timage, inter->pos.z, inter->pos.y);
	// return (intercolor);

	t_vector	axis[2];
	double		uv[3];
	int			i; // rotation
	double		a;

	a = 1 - env->form[inter->id].texture.atexture;
	// a = 1;
	axis[0] = (t_vector) {normal.y, normal.z, -normal.x};
	i = 3; // rotation
	while (--i + 1) // rotation 
		axis[0] = ft_vrotate(axis[0], env->form[inter->id].mat[i]); // rotation
	axis[1] = ft_cross(axis[0], normal);

	uv[0] = ft_dot(inter->pos, axis[0]) * 100;
	uv[1] = ft_dot(inter->pos, axis[1]) * 100;
	uv[0] -= floor(uv[0]);
	uv[1] -= floor(uv[1]);
	printf("%f, %f\n", uv[0], uv[1]);
	intercolor = rt_getcolor(env->form[inter->id].timage, uv[1], uv[0]);
	// intercolor = ft_vmul(intercolor, -a);
	return (intercolor);
}

t_vector		rt_map_cylindre(t_vector normal, t_vector intercolor,
		t_inter *inter, t_env *env)
{
	double		x;
	double		y;
	double		a;

	(void)normal;
	a = 1 - env->form[inter->id].texture.atexture;
	x = inter->pos.x;
	y = inter->pos.y;
	if (y < 0)
		y = fabs(y - 1);
	if (x < 0)
		x = fabs(x - 1);
	if (((int)x % 2 == 0 && (int)y % 2 == 0) || (((int)x + 1) % 2 == 0 &&
		((int)y + 1) % 2 == 0))
	{
		intercolor = ft_vsub(env->form[inter->id].texture.color,
			(t_vector) {1, 1, 1});
		intercolor = ft_vmul(intercolor, -a);
	}
	else
		intercolor = ft_vmul(intercolor, a);
	return (intercolor);
}

t_vector		rt_map_cone(t_vector normal, t_vector intercolor,
		t_inter *inter, t_env *env)
{
	double		o;
	double		a;

	a = 1 - env->form[inter->id].texture.atexture;
	o = atan2(ft_dot(normal, (t_vector) {0, 0, 1}), ft_dot(normal,
		(t_vector) {1, 0, 0})) / M_PI * env->form[inter->id].texture.recurrence;
	if (o < 0)
		o = fabs(o - 1);
	if (((int)o % 2 == 0 && (int)inter->pos.y % 2 == 0) ||
		(((int)o + 1) % 2 == 0 && ((int)inter->pos.y + 1) % 2 == 0))
	{
		intercolor = ft_vsub(env->form[inter->id].texture.color, (t_vector) {1, 1, 1});
		intercolor = ft_vmul(intercolor, -a);
	}
	else
		intercolor = ft_vmul(intercolor, a);
	return (intercolor);
}

t_vector			rt_tmap(t_vector normal, t_vector intercolor, t_env *env,
						t_inter *inter)
{
	static int		tftype[NBR_FORM] = {SPHERE, PLAN, CYLINDRE, CONE};
	static t_vector	(*func[NBR_FORM])(t_vector, t_vector, t_inter*,
		t_env*) = {rt_map_sphere, rt_map_plan,
		rt_map_cylindre, rt_map_cone};
	int				i;

	i = -1;
	while (++i < NBR_FORM)
	{
		if (env->form[inter->id].ftype == tftype[i])
			intercolor = func[i](normal, intercolor, inter, env);
	}
	(void)normal;
	(void)env;
	(void)intercolor;
	(void)inter;
	return (intercolor);
}

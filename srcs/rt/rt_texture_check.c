/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_texture_check.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoussa <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/26 17:37:10 by mmoussa           #+#    #+#             */
/*   Updated: 2019/06/26 17:37:11 by mmoussa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "rt.h"

t_vector		rt_checker_sphere(t_vector normal, t_vector intercolor,
		t_inter *inter, t_env *env)
{
	double		o;
	double		p;
	double		a;

	(void)inter;
	a = 1 - env->form[inter->id].texture.atexture;
	p = acos(-1 * ft_dot(normal, (t_vector) {0, 1, 0}))
		/ M_PI * env->form[inter->id].texture.recurrence;
	o = atan2(ft_dot(normal, (t_vector) {0, 0, 1}), ft_dot(normal,
		(t_vector) {1, 0, 0})) / M_PI * env->form[inter->id].texture.recurrence;
	if (o < 0)
		o = fabs(o - 1);
	if (((int)p % 2 == 0 && (int)o % 2 == 0) ||
		(((int)p + 1) % 2 == 0 && ((int)o + 1) % 2 == 0))
	{
		intercolor = ft_vsub(env->form[inter->id].texture.color,
			(t_vector) {1, 1, 1});
		intercolor = ft_vmul(intercolor, -a);
	}
	else
		intercolor = ft_vmul(intercolor, a);
	return (intercolor);
}

t_vector		rt_checker_plan(t_vector normal, t_vector intercolor,
		t_inter *inter, t_env *env)
{
	t_vector	axis[2];
	double		uv[3];
	double		a;

	a = 1 - env->form[inter->id].texture.atexture;
	axis[0] = (t_vector) {normal.y, normal.z, -normal.x};
	axis[1] = ft_cross(axis[0], normal);
	uv[0] = cos(ft_dot(inter->pos, axis[0]) / env->form[inter->id].texture.recurrence);
	uv[1] = cos(ft_dot(inter->pos, axis[1]) / env->form[inter->id].texture.recurrence);
	uv[2] = cos(ft_dot(inter->pos, normal) / env->form[inter->id].texture.recurrence);
	if (((uv[0] * uv[1] * uv[2]) > 0))
	{
		intercolor = ft_vsub(env->form[inter->id].texture.color,
			(t_vector) {1, 1, 1});
		intercolor = ft_vmul(intercolor, -a);
	}
	else
		intercolor = ft_vmul(intercolor, a);
	return (intercolor);
}

t_vector		rt_checker_cylindre(t_vector normal, t_vector intercolor,
		t_inter *inter, t_env *env)
{
	double		x;
	double		y;
	double		a;

	(void)normal;
	a = 1 - env->form[inter->id].texture.atexture;
	x = cos(inter->pos.x * env->form[inter->id].texture.recurrence);
	y = sin(inter->pos.y * env->form[inter->id].texture.recurrence);
	if (x * y > 0)
	{
		intercolor = ft_vsub(env->form[inter->id].texture.color,
			(t_vector) {1, 1, 1});
		intercolor = ft_vmul(intercolor, -a);
	}
	else
		intercolor = ft_vmul(intercolor, a);
	return (intercolor);
}

t_vector		rt_checker_cone(t_vector normal, t_vector intercolor,
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

t_vector		rt_tchecker(t_vector normal, t_vector intercolor, t_env *env,
					t_inter *inter)
{
	static int		tftype[NBR_FORM] = {SPHERE, PLAN, CYLINDRE, CONE};
	static t_vector	(*func[NBR_FORM])(t_vector, t_vector, t_inter*,
		t_env*) = {rt_checker_sphere, rt_checker_plan,
		rt_checker_cylindre, rt_checker_cone};
	int				i;

	i = -1;
	while (++i < NBR_FORM)
	{
		if (env->form[inter->id].ftype == tftype[i])
			intercolor = func[i](normal, intercolor, inter, env);
	}
	return (intercolor);
}

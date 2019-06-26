/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_texture.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoussa <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/25 18:25:07 by mmoussa           #+#    #+#             */
/*   Updated: 2019/06/25 18:25:09 by mmoussa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "rt.h"

t_vector		rt_checker_sphere(t_vector normal, t_vector intercolor, t_inter *inter, t_form *form)
{
	double		o;
	double		p;
	double		a;
	t_vector	c[3];

	(void)form;
	(void)inter;
	ft_bzero(&c, sizeof(t_vector) * 3);
	c[0].x = 1;
	c[1].y = 1;
	c[2].z = 1;
	a = 1; /* ALPHA */
	p = acos(-1 * ft_dot(normal, c[1])) / M_PI * 10; /* RECURENCE*/
	o = atan2(ft_dot(normal, c[2]), ft_dot(normal, c[0])) / M_PI * 10;
	if (o < 0)
		o = fabs(o - 1);
	if (((int)p % 2 == 0 && (int)o % 2 == 0) ||
		(((int)p + 1) % 2 == 0 && ((int)o + 1) % 2 == 0))
		intercolor = ft_vmul(intercolor, -a);
	else
		intercolor = ft_vmul(intercolor, a);
	return intercolor;
}

t_vector		rt_checker_plan(t_vector normal, t_vector intercolor, t_inter *inter, t_form *form)
{
	t_vector	axis[2];
	double		uv[2];
	double		a;

	(void)normal;
	(void)form;
	a = 0.9; /* ALPHA */
	axis[0] = (t_vector) {normal.y, normal.z, -normal.x};
	axis[1] = ft_cross(axis[0], normal);
	uv[0] = cos(ft_dot(inter->pos, axis[0])) * 10;
	uv[1] = tan(ft_dot(inter->pos, axis[1])) * 10;
	// uv[0] -= floor(uv[0]);
	// uv[1] -= floor(uv[1]);
	// printf("%f, %f\n", uv[0], uv[1]);
	if (uv[0] > 0)
		intercolor = ft_vmul(intercolor, -a);
	else
		intercolor = ft_vmul(intercolor, a);
	return intercolor;
}

t_vector		rt_checker_cylindre(t_vector normal, t_vector intercolor, t_inter *inter, t_form *form)
{
	double		o;
	double		p;
	double		a;
	t_vector	c[3];

	(void)form;
	(void)inter;
	ft_bzero(&c, sizeof(t_vector) * 3);
	c[0].x = 1;
	c[1].y = 1;
	c[2].z = 1;
	a = 0.8; /* ALPHA */
	p = acos(-1 * ft_dot(normal, c[1])) / M_PI * 50; /* RECURENCE*/
	o = atan2(ft_dot(normal, c[2]), ft_dot(normal, c[0])) / M_PI * 50;
	if (o < 0)
		o = fabs(o - 1);
	if (((int)p % 2 == 0 && (int)o % 2 == 0) ||
		(((int)p + 1) % 2 == 0 && ((int)o + 1) % 2 == 0))
		intercolor = ft_vmul(intercolor, -a);
	else
		intercolor = ft_vmul(intercolor, a);
	return intercolor;
}

t_vector		rt_checker_cone(t_vector normal, t_vector intercolor, t_inter *inter, t_form *form)
{
	double		o;
	double		p;
	double		a;
	t_vector	c[3];

	(void)form;
	(void)inter;
	ft_bzero(&c, sizeof(t_vector) * 3);
	c[0].x = 1;
	c[1].y = 1;
	c[2].z = 1;
	a = 0.8; /* ALPHA */
	p = acos(-1 * ft_dot(normal, c[1])) / M_PI * 20; /* RECURENCE*/
	o = atan2(ft_dot(normal, c[2]), ft_dot(normal, c[0])) / M_PI * 20;
	if (o < 0)
		o = fabs(o - 1);
	if (((int)p % 2 == 0 && (int)o % 2 == 0) ||
		(((int)p + 1) % 2 == 0 && ((int)o + 1) % 2 == 0))
		intercolor = ft_vmul(intercolor, -a);
	else
		intercolor = ft_vmul(intercolor, a);
	return intercolor;
}

t_vector		rt_tchecker(t_vector normal, t_vector intercolor, t_form *form,
					t_inter *inter)
{
	static int		tftype[NBR_FORM] = {SPHERE, PLAN, CYLINDRE, CONE};
	static t_vector	(*func[NBR_FORM])(t_vector, t_vector, t_inter*, t_form*) = {rt_checker_sphere,
						rt_checker_plan, rt_checker_cylindre, rt_checker_cone};
	int				i;

	i = -1;
	while (++i < NBR_FORM)
	{
		if (form->ftype == tftype[i])
			intercolor = func[i](normal, intercolor, inter, form);
	}
	return (intercolor);
}

t_vector		rt_tnothing(t_vector normal, t_vector intercolor, t_form *form, t_inter *inter)
{
	(void)normal;
	(void)form;
	(void)inter;
	return (intercolor);
}

void			rt_get_texture(t_etexture texture, t_vector normal, t_form *form,
	t_inter *inter)
{
	static int		ttext[2] = {TNOTHING, TCHECKER};
	static t_vector	(*func[2])(t_vector, t_vector, t_form*, t_inter*) = {rt_tnothing,
						rt_tchecker};
	int				i;

	i = 3;
	while (--i + 1)
		normal = ft_vrotate(normal, form->mat[i]);
	while (++i < 2)
	{
		if (texture == ttext[i])
			inter->color = ft_vadd(inter->color,
				(func[i](normal, inter->color, form, inter)));
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_basics_normal.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roliveir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/09 20:42:41 by roliveir          #+#    #+#             */
/*   Updated: 2019/07/11 18:15:16 by oboutrol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "rt.h"

static t_vector			rt_norm_sphere(t_vector pos, t_form form)
{
	(void)form;
	return (ft_normalize(pos));
}

static t_vector			rt_norm_plan(t_vector pos, t_form form)
{
	t_vector			norm;

	(void)form;
	(void)pos;
	ft_bzero(&norm, sizeof(t_vector));
	norm.y = 1;
	return (norm);
}

static t_vector			rt_norm_cylindre(t_vector pos, t_form form)
{
	t_vector			norm;

	norm.x = form.r * (pos.x / (sqrt(pow(pos.x, 2) + pow(pos.z, 2))));
	norm.z = form.r * (pos.z / (sqrt(pow(pos.x, 2) + pow(pos.z, 2))));
	norm.y = 0.0;
	return (ft_normalize(norm));
}

static t_vector			rt_norm_cone(t_vector pos, t_form form)
{
	t_vector			norm;
	double				neg;

	neg = pos.y < 0 ? 1 : -1;
	norm.x = pos.x * cos(form.angle);
	norm.z = pos.z * cos(form.angle);
	norm.y = sin(form.angle) * neg;
	return (ft_normalize(norm));
}

t_vector				rt_get_normal(t_vector pos, t_form form, t_vector vdir)
{
	static t_vector		(*func[NBR_FORM - 2])(t_vector, t_form) = {
		rt_norm_sphere, rt_norm_plan, rt_norm_cylindre, rt_norm_cone,
		rt_norm_torus, rt_norm_hyper, rt_norm_cubet};
	t_vector			bump;

	bump = (t_vector) {0, 0, 0};
	if (form.texture.bump_type == BCOS)
		rt_bump_cos(&bump, pos, form);
	else if (form.texture.bump_type == BWATER)
		rt_bump_water(&bump, pos, form);
	else if (form.texture.bump_type == BSAND)
		rt_bump_idk(&bump, pos, form);
	if (ft_dot(bump, vdir) > 0)
		bump = ft_vmul(bump, -1);
	return (ft_normalize(ft_vadd(func[form.ftype](pos, form), bump)));
}

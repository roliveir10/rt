/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   comp_cube.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutrol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/11 10:17:05 by oboutrol          #+#    #+#             */
/*   Updated: 2019/07/12 16:45:24 by oboutrol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pars.h"
#include <math.h>

t_lstform			*setup_form(t_form form, double offset[3], double rot[3])
{
	t_lstform		*first;
	double			mat[3][3][3];

	if (!(first = (t_lstform*)ft_memalloc(sizeof(t_lstform))))
		return (NULL);
	first->form = form;
	first->form.ftype = PLAN;
	first->form.max.x = form.r;
	first->form.max.z = form.r;
	first->form.min.x = -form.r;
	first->form.min.z = -form.r;
	first->form.fields[MAX] = 1;
	first->form.fields[MIN] = 1;
	first->form.rotation.x += rot[0];
	first->form.rotation.y += rot[1];
	first->form.rotation.z += rot[2];
	ft_fmat(&mat, form.rotation, 1);
	first->form.center.x += offset[0];
	first->form.center.y += offset[1];
	first->form.center.z += offset[2];
	first->form.center = ft_vrotate(first->form.center, mat[0]);
	first->form.center = ft_vrotate(first->form.center, mat[1]);
	first->form.center = ft_vrotate(first->form.center, mat[2]);
	return (first);
}

static void			set_elm(double tab[3], double a, double b, double c)
{
	tab[0] = a;
	tab[1] = b;
	tab[2] = c;
}

t_lstform			*part_cube(t_form form)
{
	t_lstform		*first;
	t_lstform		*others;
	t_lstform		*old;
	double			offset[3];
	double			rot[3];

	set_elm(rot, 0, 0, 90);
	set_elm(offset, -form.r, 0, 0);
	rot[2] = 90;
	offset[0] = -form.r;
	if (!(first = setup_form(form, offset, rot)))
		return (NULL);
	set_elm(rot, 90, 0, 0);
	set_elm(offset, 0, 0, form.r);
	if (!(others = setup_form(form, offset, rot)))
		return (first);
	first->next = others;
	old = others;
	offset[2] = -form.r;
	if (!(others = setup_form(form, offset, rot)))
		return (first);
	old->next = others;
	return (first);
}

t_lstform			*comp_cube(t_form form)
{
	t_lstform		*first;
	t_lstform		*others;
	t_lstform		*old;
	double			offset[3];
	double			rot[3];

	ft_bzero(offset, sizeof(double[3]));
	ft_bzero(rot, sizeof(double[3]));
	offset[1] = form.r;
	if (!(first = setup_form(form, offset, rot)))
		return (NULL);
	offset[1] = -form.r;
	if (!(others = setup_form(form, offset, rot)))
		return (first);
	first->next = others;
	old = others;
	set_elm(rot, 0, 0, 90);
	set_elm(offset, form.r, 0, 0);
	if (!(others = setup_form(form, offset, rot)))
		return (first);
	old->next = others;
	old->next = part_cube(form);
	return (first);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   comp_cube.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutrol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/11 10:17:05 by oboutrol          #+#    #+#             */
/*   Updated: 2019/07/11 17:04:45 by oboutrol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pars.h"
#include <math.h>

#include <stdio.h>
t_lstform		*setup_form(t_form form, double offset[3], double rot[3])
{
	t_lstform	*first;
	double		mat[3][3][3];

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

t_lstform			*comp_cube(t_form form)
{
	t_lstform		*first;
	t_lstform		*others;
	t_lstform		*old;
	double			offset[3] = {0, 0, 0};
	double			rot[3] = {0, 0, 0};

	offset[1] = form.r;
	if (!(first = setup_form(form, offset, rot)))
		return (NULL);

	offset[1] = -form.r;
	if (!(others = setup_form(form, offset, rot)))
		return (first);
	first->next = others;
	old = others;

	rot[2] = 90;
	offset[1] = 0;
	offset[0] = form.r;
	if (!(others = setup_form(form, offset, rot)))
		return (first);
	old->next = others;
	old = others;

	rot[2] = 90;
	offset[0] = -form.r;
	if (!(others = setup_form(form, offset, rot)))
		return (first);
	old->next = others;
	old = others;

	rot[2] = 0;
	rot[0] = 90;
	offset[0] = 0;
	offset[2] = form.r;
	if (!(others = setup_form(form, offset, rot)))
		return (first);
	old->next = others;
	old = others;

	offset[2] = -form.r;
	if (!(others = setup_form(form, offset, rot)))
		return (first);
	old->next = others;
	return (first);
}

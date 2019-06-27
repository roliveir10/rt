/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_form.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutrol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/25 23:45:53 by oboutrol          #+#    #+#             */
/*   Updated: 2019/06/26 02:01:27 by oboutrol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pars.h"
#include "libft.h"

void		*set_rotation_form(t_form *form, t_token **token)
{
	form->rotation = pars_vector(token);
	if (form->fields[ROTATION])
		print_warning("redifinition of Rotation field");
	form->fields[ROTATION] = 1;
	return (NULL);
}

void		*set_direct_form(t_form *form, t_token **token)
{
	form->direct = pars_vector(token);
	if (form->fields[DIRECT])
		print_warning("redifinition of Direct field");
	form->fields[DIRECT] = 1;
	return (NULL);
}

void		*set_point_form(t_form *form, t_token **token)
{
	form->point = pars_vector(token);
	if (form->fields[POINT])
		print_warning("redifinition of Point field");
	form->fields[POINT] = 1;
	return (NULL);
}

void		*set_origin_form(t_form *form, t_token **token)
{
	form->center = pars_vector(token);
	if (form->fields[ORIGIN])
		print_warning("redifinition of Origin field");
	form->fields[ORIGIN] = 1;
	return (NULL);
}

void		*set_color_form(t_form *form, t_token **token)
{
	form->color = pars_vector_color(token);
	if (form->fields[COLOR])
		print_warning("redifinition of Color field");
	form->fields[COLOR] = 1;
	return (NULL);
}

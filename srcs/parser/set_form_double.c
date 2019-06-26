/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_form_double.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutrol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/26 02:01:40 by oboutrol          #+#    #+#             */
/*   Updated: 2019/06/26 02:15:45 by oboutrol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pars.h"
#include "libft.h"

void		*set_radius_form(t_form *form, t_token **token)
{
	form->r = pars_double(token);
	if (form->fields[RADIUS])
		print_warning("redifinition of Radius field");
	form->fields[RADIUS] = 1;
	return (NULL);
}

void		*set_height_form(t_form *form, t_token **token)
{
	form->h = pars_double(token);
	if (form->fields[HEIGHT])
		print_warning("redifinition of Height field");
	form->fields[HEIGHT] = 1;
	return (NULL);
}

void		*set_angle_form(t_form *form, t_token **token)
{
	form->angle = pars_double(token);
	if (form->fields[ANGLE])
		print_warning("redifinition of Angle field");
	form->fields[ANGLE] = 1;
	return (NULL);
}

void		*set_name_form(t_form *form, t_token **token)
{
	form->ftype = pars_name(token);
	if (form->fields[NAME])
		print_warning("redifinition of Name field");
	form->fields[NAME] = 1;
	return (NULL);
}

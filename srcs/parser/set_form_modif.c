/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_form_modif.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutrol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/12 13:59:15 by oboutrol          #+#    #+#             */
/*   Updated: 2019/07/12 14:02:21 by oboutrol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pars.h"
#include "libft.h"

void		*set_transp_form(t_form *form, t_token **token)
{
	form->itpy = pars_double(token);
	if (form->fields[TRANSP])
		print_warning("redifinition of Reflection field");
	form->fields[TRANSP] = 1;
	return (NULL);
}

void		*set_density_form(t_form *form, t_token **token)
{
	form->irefr = pars_double(token);
	if (form->fields[DENSITY])
		print_warning("redifinition of Reflection field");
	form->fields[DENSITY] = 1;
	return (NULL);
}

void		*set_offsetx_form(t_form *form, t_token **token)
{
	form->texture.offsetx = pars_double(token);
	if (form->fields[OFFX])
		print_warning("redifinition of Offset X field");
	form->fields[OFFX] = 1;
	return (NULL);
}

void		*set_offsety_form(t_form *form, t_token **token)
{
	form->texture.offsety = pars_double(token);
	if (form->fields[OFFY])
		print_warning("redifinition of Offset Y field");
	form->fields[OFFY] = 1;
	return (NULL);
}

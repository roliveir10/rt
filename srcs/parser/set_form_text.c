/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_form_text.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutrol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/26 06:24:03 by oboutrol          #+#    #+#             */
/*   Updated: 2019/06/26 06:58:45 by oboutrol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pars.h"
#include "libft.h"

void		*set_texture_form(t_form *form, t_token **token)
{
	form->texture.type = pars_texture(token);
	if (form->fields[TEXT])
		print_warning("redefinition of Texture field");
	form->fields[TEXT] = 1;
	return (NULL);
}

void		*set_atexture_form(t_form *form, t_token **token)
{
	form->texture.atexture = pars_double(token);
	if (form->fields[ATEXT])
		print_warning("redefinition of AlphaTexture field");
	form->fields[ATEXT] = 1;
	return (NULL);
}

void		*set_scale_form(t_form *form, t_token **token)
{
	form->texture.scale = (int)pars_double(token);
	if (form->fields[REC])
		print_warning("redefinition of Scale field");
	form->fields[REC] = 1;
	return (NULL);
}

void		*set_tcolor_form(t_form *form, t_token **token)
{
	form->texture.color = pars_vector_color(token);
	if (form->fields[TCOLOR])
		print_warning("redefinition of Texture Color field");
	form->fields[TCOLOR] = 1;
	return (NULL);
}

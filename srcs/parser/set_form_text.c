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
	form->texture = pars_texture(token);
	if (form->fields[TEXT])
		print_warning("redefinition of Texture field");
	form->fields[TEXT] = 1;
	return (NULL);
}

void		*set_atexture_form(t_form *form, t_token **token)
{
	form->atexture = pars_double(token);
	if (form->fields[ATEXT])
		print_warning("redefinition of AlphaTexture field");
	form->fields[ATEXT] = 1;
	return (NULL);
}

void		*set_recurrence_form(t_form *form, t_token **token)
{
	form->recurrence = (int)pars_double(token);
	if (form->fields[REC])
		print_warning("redefinition of Recurrence field");
	form->fields[REC] = 1;
	return (NULL);
}

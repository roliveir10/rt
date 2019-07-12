/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_form_perl.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutrol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/12 13:55:32 by oboutrol          #+#    #+#             */
/*   Updated: 2019/07/12 13:57:11 by oboutrol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pars.h"
#include "libft.h"

void		*set_pfrequ_form(t_form *form, t_token **token)
{
	form->texture.pfrequ = pars_double(token);
	if (form->fields[PFREQ])
		print_warning("redifinition of Perlin Frequency field");
	form->fields[PFREQ] = 1;
	return (NULL);
}

void		*set_pdepth_form(t_form *form, t_token **token)
{
	form->texture.pdepth = pars_double(token);
	if (form->fields[PDEPTH])
		print_warning("redifinition of Perlin Depth field");
	form->fields[PDEPTH] = 1;
	return (NULL);
}

void		*set_bfrequ_form(t_form *form, t_token **token)
{
	form->texture.bfrequ = pars_double(token);
	if (form->fields[BFREQ])
		print_warning("redifinition of Bumping Frequency field");
	form->fields[BFREQ] = 1;
	return (NULL);
}

void		*set_bdepth_form(t_form *form, t_token **token)
{
	form->texture.bdepth = pars_double(token);
	if (form->fields[BDEPTH])
		print_warning("redifinition of Bumping Depth field");
	form->fields[BDEPTH] = 1;
	return (NULL);
}

void		*set_bumpname_form(t_form *form, t_token **token)
{
	form->texture.bump_type = pars_bump(token);
	if (form->fields[BTYPE])
		print_warning("redifinition of Bumping Type field");
	form->fields[BTYPE] = 1;
	return (NULL);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_form_double.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutrol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/26 02:01:40 by oboutrol          #+#    #+#             */
/*   Updated: 2019/07/11 17:48:01 by oboutrol         ###   ########.fr       */
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

void		*set_reflection_form(t_form *form, t_token **token)
{
	form->iref = pars_double(token);
	if (form->fields[REFLECT])
		print_warning("redifinition of Reflection field");
	form->fields[REFLECT] = 1;
	return (NULL);
}

void		*set_max_form(t_form *form, t_token **token)
{
	form->max = pars_vector(token);
	if (form->fields[MAX])
		print_warning("redifinition of Max field");
	form->fields[MAX] = 1;
	return (NULL);
}

void		*set_min_form(t_form *form, t_token **token)
{
	form->min = pars_vector(token);
	if (form->fields[MIN])
		print_warning("redifinition of Min field");
	form->fields[MIN] = 1;
	return (NULL);
}

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

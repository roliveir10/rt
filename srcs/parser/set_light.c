/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_light.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutrol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/26 04:29:10 by oboutrol          #+#    #+#             */
/*   Updated: 2019/06/26 13:44:42 by oboutrol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pars.h"
#include "libft.h"

void		*set_origin_lum(t_lum *light, t_token **token)
{
	light->pos = pars_vector(token);
	if (light->fields[LUMPOS])
		print_warning("redifinition of Origin field");
	light->fields[LUMPOS] = 1;
	return (NULL);
}

void		*set_direct_lum(t_lum *light, t_token **token)
{
	light->dir = pars_vector(token);
	if (light->fields[LUMDIR])
		print_warning("redifinition of Direct field");
	light->fields[LUMDIR] = 1;
	return (NULL);
}

void		*set_color_lum(t_lum *light, t_token **token)
{
	light->color = pars_vector_color(token);
	if (light->fields[LUMCOLOR])
		print_warning("redifinition of Color field");
	light->fields[LUMCOLOR] = 1;
	return (NULL);
}

void		*set_type_lum(t_lum *light, t_token **token)
{
	light->type = pars_name_light(token);
	if (light->fields[LUMTYPE])
		print_warning("redifinition of Type field");
	light->fields[LUMTYPE] = 1;
	return (NULL);
}

void		*set_intensity_lum(t_lum *light, t_token **token)
{
	double	intensity;

	intensity = pars_double(token);
	if (!intensity)
		intensity = 0.1;
	light->constant = 1.0;
	light->linear = 0.8 * 1.0 / intensity;
	light->quadratic = 0.2 * 1.0 / intensity;
	if (light->fields[LUMINT])
		print_warning("redifinition of Intensity field");
	light->fields[LUMINT] = 1;
	return (NULL);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_light_double.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutrol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/26 13:38:02 by oboutrol          #+#    #+#             */
/*   Updated: 2019/07/03 03:38:31 by oboutrol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "pars.h"
#include "libft.h"

void		*set_cutoff_lum(t_lum *light, t_token **token)
{
	light->cutoff = cos(pars_double(token) / 180.0 * M_PI);
	if (light->fields[LUMCUT])
		print_warning("redifinition of CutOff field");
	light->fields[LUMCUT] = 1;
	return (NULL);
}

void		*set_outercutoff_lum(t_lum *light, t_token **token)
{
	light->outercutoff = cos(pars_double(token) / 180.0 * M_PI);
	if (light->fields[LUMOUT])
		print_warning("redifinition of Outercutoff field");
	light->fields[LUMOUT] = 1;
	return (NULL);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_light_double.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutrol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/26 13:38:02 by oboutrol          #+#    #+#             */
/*   Updated: 2019/06/26 13:44:39 by oboutrol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pars.h"
#include "libft.h"

void		*set_cutoff_lum(t_lum *light, t_token **token)
{
	light->cutoff = pars_double(token);
	if (light->fields[LUMCUT])
		print_warning("redifinition of CutOff field");
	light->fields[LUMCUT] = 1;
	return (NULL);
}


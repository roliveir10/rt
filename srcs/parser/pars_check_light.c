/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_check_light.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutrol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/26 05:21:50 by oboutrol          #+#    #+#             */
/*   Updated: 2019/06/26 05:42:05 by oboutrol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "pars.h"

int		pars_check_light(t_lum lum)
{
	int	ret;

	ret = 0;
	if (!lum.fields[LUMPOS])
		ret = print_no_field("origin", "light", "element");
	if (!lum.fields[LUMCOLOR])
		ret = print_no_field("color", "light", "element");
	if (!lum.fields[LUMTYPE])
		ret = print_no_field("type", "light", "element");
	if (ret)
		ft_putstr_fd("rt: Warning: Dropping Light\n", 2);
	return (ret);
}

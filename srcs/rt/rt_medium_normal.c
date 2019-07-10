/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_medium_normal.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutrol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/02 15:36:01 by oboutrol          #+#    #+#             */
/*   Updated: 2019/07/06 13:45:03 by oboutrol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "rt.h"

t_vector				rt_norm_torus(t_vector pos, t_form form)
{
	double				alpha;
	t_vector			norm;

	alpha = form.r / sqrt(pos.x * pos.x + pos.y * pos.y);
	norm.x = (1 - alpha) * pos.x;
	norm.y = (1 - alpha) * pos.y;
	norm.z = pos.z;
	return (ft_normalize(norm));
}

t_vector				rt_norm_hyper(t_vector pos, t_form form)
{
	(void)form;
	return (ft_normalize(pos));
}

t_vector				rt_norm_cubet(t_vector pos, t_form form)
{
	t_vector			norm;

	(void)form;
	norm.x = 4 * pow(pos.x, 3) - 10 * pos.x;
	norm.y = 4 * pow(pos.y, 3) - 10 * pos.y;
	norm.z = 4 * pow(pos.z, 3) - 10 * pos.z;
	return (ft_normalize(norm));
}

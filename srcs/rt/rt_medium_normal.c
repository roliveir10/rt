/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_medium_normal.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutrol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/02 15:36:01 by oboutrol          #+#    #+#             */
/*   Updated: 2019/07/04 14:15:05 by oboutrol         ###   ########.fr       */
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

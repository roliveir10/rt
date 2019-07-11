/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_inter_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roliveir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/11 14:19:46 by roliveir          #+#    #+#             */
/*   Updated: 2019/07/11 14:22:18 by roliveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

double				rt_first_inter(t_env *env, t_ray ray_o, t_inter *inter)
{
	int				i;
	double			min;
	t_ray			ray;

	i = -1;
	min = -1.0;
	while (++i < env->nbr_form)
	{
		ray = ray_o;
		if (rt_shape_inter(env, &i, &ray, &min))
		{
			inter->id = i;
			inter->pos = rt_get_posinter(ray, min);
		}
	}
	return (min);
}

t_vector			rt_no_inter(void)
{
	t_vector		color_black;
	t_vector		color_sky;

	ft_bzero(&color_black, sizeof(t_vector));
	color_sky.x = 135.0 / 255.0;
	color_sky.y = 206.0 / 255.0;
	color_sky.z = 235.0 / 255.0;
	return (color_sky);
}

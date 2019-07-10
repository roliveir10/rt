/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_limits.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutrol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 07:37:42 by oboutrol          #+#    #+#             */
/*   Updated: 2019/07/06 10:53:41 by oboutrol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "pars.h"

int			is_higher(double res, t_ray *ray, t_form form)
{
	if (!form.fields[MAX])
		return (0);
	if (form.max.x && res * ray->dir.x + ray->o.x > form.max.x)
		return (1);
	if (form.max.y && res * ray->dir.y + ray->o.y > form.max.y)
		return (1);
	if (form.max.z && res * ray->dir.z + ray->o.z > form.max.z)
		return (1);
	return (0);
}

int			is_lower(double res, t_ray *ray, t_form form)
{
	if (!form.fields[MIN])
		return (0);
	if (form.min.x && res * ray->dir.x + ray->o.x < form.min.x)
		return (1);
	if (form.min.y && res * ray->dir.y + ray->o.y < form.min.y)
		return (1);
	if (form.min.z && res * ray->dir.z + ray->o.z < form.min.z)
		return (1);
	return (0);
}

int			is_planed(double res, t_ray *ray, t_form form)
{
	double	x;
	double	y;

	if (form.ftype == PLAN && form.fields[POINT] && form.fields[RADIUS])
	{
		x =	res * ray->dir.x + ray->o.x - form.point.x;
		y =	res * ray->dir.z + ray->o.z - form.point.z;
		if (x * x + y * y > form.r * form.r)
			return (1);
	}
	return (0);
}

double		rt_limit(double res, t_ftype ftype, t_ray *ray, t_form form)
{
	t_ray	newray;
	int		k;
	double	newres;

	if (res < 0)
		return (res);
	newray = *ray;
	k = 0;
	while (k < 6)
	{
		if (is_higher(res, ray, form) || is_lower(res, ray, form)
				|| is_planed(res, ray, form))
		{
			newray.o = rt_get_posinter(*ray, res + 0.2);
			if ((newres = rt_selectf(ftype, &newray, form)) < 0)
				return (-1);
			res = newres + res + 0.2;
		}
		k++;
	}
	return (res);
}

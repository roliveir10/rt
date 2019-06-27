/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_rotation.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roliveir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/12 04:57:13 by roliveir          #+#    #+#             */
/*   Updated: 2019/06/27 17:08:08 by roliveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "rt.h"

void		rt_set_ref(t_ray *ray, t_form form)
{
	int		i;

	i = -1;
	ray->o = ft_vsub(form.center, ray->o);
	while (++i < 3)
	{
		ray->dir = ft_vrotate(ray->dir, form.mat[i]);
		ray->o = ft_vrotate(ray->o, form.mat[i]);
	}
}

void		rt_reset_point(t_form form, t_vector *inte)
{
	int		i;

	i = 3;
	while (--i + 1)
		*inte = ft_vrotate(*inte, form.mati[i]);
	*inte = ft_vadd(*inte, form.center);
}

void		rt_initialize_rotation(t_env *env)
{
	int		i;
	int		j;
	double	cmat[3][3][3];

	i = -1;
	while (++i < env->nbr_form)
	{
		ft_fmat(&env->form[i].mat, env->form[i].rotation, -1);
		ft_fmat(&env->form[i].mati, env->form[i].rotation, 1);
	}
	i = -1;
	ft_fmat(&cmat, env->cam.rotation, -1);
	while (++i < 3)
	{
		j = -1;
		while (++j < 3)
			env->cam.vec_dir[i] = ft_vrotate(env->cam.vec_dir[i], cmat[j]);
	}
	i = -1;
	while (++i < env->nbr_lum)
		env->lum[i].dir = ft_normalize(env->lum[i].dir);
}

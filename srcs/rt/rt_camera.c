/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_camera.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roliveir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/20 04:16:17 by roliveir          #+#    #+#             */
/*   Updated: 2019/06/24 03:25:46 by roliveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void				rt_update_campos(t_cam *cam)
{
	t_vector		vx;
	t_vector		vy;
	t_vector		vz;

	vz = ft_vmul(cam->vec_dir[2], cam->vp_dist);
	vy = ft_vmul(cam->vec_dir[1], cam->vp_height / 2.0);
	vx = ft_vmul(cam->vec_dir[0], cam->vp_width / 2.0);
	cam->vp_upleft.x = cam->pos.x + vz.x + vy.x - vx.x;
	cam->vp_upleft.y = cam->pos.y + vz.y + vy.y - vx.y;
	cam->vp_upleft.z = cam->pos.z + vz.z + vy.z - vx.z;
}

void				rt_update_camrot(t_cam *cam, double mat[3][3][3])
{
	int				i;

	i = -1;
	while (++i < 3)
	{
		cam->vec_dir[0] = ft_vrotate(cam->vec_dir[0], mat[i]);
		cam->vec_dir[1] = ft_vrotate(cam->vec_dir[1], mat[i]);
		cam->vec_dir[2] = ft_vrotate(cam->vec_dir[2], mat[i]);
	}
	rt_update_campos(cam);
}

void				rt_movecam_pos(t_env *env, int keycode)
{
	env->key_repeat = 1;
	if (keycode == KLEFT)
		env->cam.pos.x -= SCREENX / 500;
	else if (keycode == KRIGHT)
		env->cam.pos.x += SCREENX / 500;
	else if (keycode == KUP)
		env->cam.pos.y += SCREENY / 500;
	else if (keycode == KDOWN)
		env->cam.pos.y -= SCREENY / 500;
	rt_update_campos(&env->cam);
	env->offset = PIX;
}

void				rt_mmovecam_pos(t_env *env, int keycode)
{
	if (keycode == MUP)
		env->cam.pos.z -= SCREENX / 250;
	else if (keycode == MDOWN)
		env->cam.pos.z += SCREENX / 250;
	rt_update_campos(&env->cam);
	env->offset = PIX;
}

void				rt_movecam_rot(t_env *env, int keycode)
{
	double			mat[3][3][3];
	t_vector		rotation;
	double			neg;

	neg = 1;
	env->key_repeat = 1;
	ft_bzero(&rotation, sizeof(t_vector));
	if (keycode == KRXUP || keycode == KRYRIGHT || keycode == KRZRIGHT)
		neg = -1;
	if (keycode == KRXUP || keycode == KRXDOWN)
		rotation.x = 1.0;
	else if (keycode == KRYRIGHT || keycode == KRYLEFT)
		rotation.y = 1.0;
	else if (keycode == KRZRIGHT || keycode == KRZLEFT)
		rotation.z = 1.0;
	ft_fmat(&mat, rotation, neg);
	rt_update_camrot(&env->cam, mat);
	env->offset = PIX;
}

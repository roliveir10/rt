/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_menu.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atelli <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/03 17:58:20 by atelli            #+#    #+#             */
/*   Updated: 2019/07/03 17:58:24 by atelli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "mlx.h"

void		rt_menu_campos(t_env *env)
{
	char		*test;
	char		*camposx;
	char		*camposy;
	char		*camposz;

	camposx = ft_itoa(env->cam.pos.x);
	camposy = ft_itoa(env->cam.pos.y);
	camposz = ft_itoa(env->cam.pos.z);
	test = ft_strjoin("X: ", camposx);
	mlx_string_put(env->mlx.mlx, env->mlx.id_interface, 10, 10, \
				0xFFFFFF, "Camera Position :");
	mlx_string_put(env->mlx.mlx, env->mlx.id_interface, 50, 35, 0xFFFFFF, test);
	ft_strdel(&test);
	test = ft_strjoin("Y: ", camposy);
	mlx_string_put(env->mlx.mlx, env->mlx.id_interface, 50, 50, 0xFFFFFF, test);
	ft_strdel(&test);
	test = ft_strjoin("Z: ", camposz);
	mlx_string_put(env->mlx.mlx, env->mlx.id_interface, 50, 65, 0xFFFFFF, test);
	ft_strdel(&camposx);
	ft_strdel(&camposy);
	ft_strdel(&camposz);
	ft_strdel(&test);
}

void		rt_menu_camrotation(t_env *env)
{
	char		*test;
	char		*camrotx;
	char		*camroty;
	char		*camrotz;

	camrotx = ft_itoa(env->cam.rotation.x);
	camroty = ft_itoa(env->cam.rotation.y);
	camrotz = ft_itoa(env->cam.rotation.z);
	test = ft_strjoin("X: ", camrotx);
	mlx_string_put(env->mlx.mlx, env->mlx.id_interface, 10, 90, \
				0xFFFFFF, "Camera Rotation :");
	mlx_string_put(env->mlx.mlx, env->mlx.id_interface, 50, 115, 0xFFFFFF, test);
	ft_strdel(&test);
	test = ft_strjoin("Y: ", camroty);
	mlx_string_put(env->mlx.mlx, env->mlx.id_interface, 50, 130, 0xFFFFFF, test);
	ft_strdel(&test);
	test = ft_strjoin("Z: ", camrotz);
	mlx_string_put(env->mlx.mlx, env->mlx.id_interface, 50, 145, 0xFFFFFF, test);
	ft_strdel(&camrotx);
	ft_strdel(&camroty);
	ft_strdel(&camrotz);
	ft_strdel(&test);
}

void		rt_menu(t_env *env)
{
	mlx_put_image_to_window(env->mlx.mlx, env->mlx.id_interface,
				env->mlx.interface, 0, 0);
	rt_menu_campos(env);
	rt_menu_camrotation(env);
}
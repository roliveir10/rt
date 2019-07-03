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

void		rt_menu(t_env *env)
{
	char		*test;
	char		*camposy;

	camposy = ft_itoa(env->cam.pos.y);
	test = ft_strjoin("Y: ", camposy);
	mlx_put_image_to_window(env->mlx.mlx, env->mlx.id_interface,
				env->mlx.interface, 0, 0);
	mlx_string_put(env->mlx.mlx, env->mlx.id_interface, 50, 50, 0xFFFFFF, test);
	ft_strdel(&camposy);
	ft_strdel(&test);
}

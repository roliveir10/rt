/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roliveir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/07 10:32:59 by roliveir          #+#    #+#             */
/*   Updated: 2019/06/25 09:17:03 by roliveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "pars.h"
#include "rt.h"

void			pars_fill_cam(t_cam *cam)
{
	cam->vec_dir[0].x = 1.0;
	cam->vec_dir[1].y = 1.0;
	cam->vec_dir[2].z = 1.0;
	cam->vp_width = SCREENX;
	cam->vp_height = SCREENY;
	cam->vp_dist = 1000;
	cam->pos.x = 0.0;
	cam->pos.y = 0.0;
	cam->pos.z = -30.0;
}

int				main(int argc, char **argv)
{
	t_env		env;

	if (argc != 2)
	{
		ft_putstr_fd("usage: rt file.json\n", 2);
		return (1);
	}
	ft_bzero(&env, sizeof(t_env));
	if (pars_file(argv[1], &env))
		return (1);
	rt_main(&env);
	return (0);
}

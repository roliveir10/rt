/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_anti_aliasing.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roliveir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/23 13:00:00 by roliveir          #+#    #+#             */
/*   Updated: 2019/06/24 14:32:42 by roliveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <mlx.h>
#include "rt.h"

static void				rt_get_origin(t_ray (*ray)[], t_vector pos)
{
	int					i;

	i = -1;
	while (++i < 4)
		(*ray)[i].o = pos;
}

static t_vector			rt_getaverage(t_ray (*ray)[], t_env *env, int pos)
{
	int					i;
	t_vector			color[4];
	t_vector			average;
	static double		vx[4] = {0, 1, 0, 1};
	static double		vy[4] = {0, 0, 1, 1};

	i = -1;
	while (++i < 4)
	{
		(*ray)[i].dir = rt_get_vecdir(env->cam, (double)(pos % SCREENX)
				+ vx[i], (double)(pos / SCREENX) + vy[i]);
		color[i] = rt_viewdir_inter(env, (*ray)[i]);
	}
	average.x = (color[0].x + color[1].x + color[2].x + color[3].x) / 4;
	average.y = (color[0].y + color[1].y + color[2].y + color[3].y) / 4;
	average.z = (color[0].z + color[1].z + color[2].z + color[3].z) / 4;
	return (average);
}

static void				*rt_print_line_aa(void *param)
{
	t_env				*env;
	t_ray				ray[4];
	int					pos;
	int					limit;
	t_vector			color_average;

	env = (t_env*)param;
	limit = SCREENX * (env->line_id + 1);
	if (limit >= SCREEN)
		limit = SCREEN - 1;
	pos = env->line_id * SCREENX;
	env->line_id++;
	rt_get_origin(&ray, env->cam.pos);
	while (pos < limit)
	{
		color_average = rt_getaverage(&ray, env, pos);
		rt_add_pixel(env, color_average, pos);
		pos++;
	}
	return (env);
}

int						rt_antialiasing(t_env *env)
{
	static char			aliasing = 0;
	int					pos;

	if (env->offset)
		aliasing = 0;
	if (env->scene.aa && !aliasing && !env->offset)
	{
		pos = 0;
		while (pos < SCREEN)
		{
			rt_thread((void*)env, rt_print_line_aa);
			pos += SCREENX * NBR_THREAD;
		}
		mlx_put_image_to_window(env->mlx.mlx, env->mlx.id,
				env->mlx.image, 0, 0);
		aliasing = 1;
		env->line_id = 0;
	}
	return (0);
}

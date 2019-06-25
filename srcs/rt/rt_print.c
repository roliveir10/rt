/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_print.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roliveir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/07 11:05:07 by roliveir          #+#    #+#             */
/*   Updated: 2019/06/24 02:53:08 by roliveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <math.h>
#include <pthread.h>
#include "rt.h"

void					rt_add_pixel(t_env *env, t_vector color, int pos)
{
	unsigned char		rgb[3];
	unsigned int		color_rgb;
	int					size;

	size = -1;
	rgb[0] = (unsigned char)(ft_clamp(pow(color.x, .454545), 0, 1) * 255);
	rgb[1] = (unsigned char)(ft_clamp(pow(color.y, .454545), 0, 1) * 255);
	rgb[2] = (unsigned char)(ft_clamp(pow(color.z, .454545), 0, 1) * 255);
	color_rgb = (rgb[0] << 16) | (rgb[1] << 8) | rgb[2];
	while (++size < env->offset)
	{
		env->mlx.mem_image[pos + size] = color_rgb;
		if (pos - size + SCREENX < SCREEN)
			env->mlx.mem_image[pos + size + SCREENX] = color_rgb;
	}
}

static void				*rt_print_line(void *param)
{
	t_ray				ray;
	int					pos;
	int					limit;
	t_vector			color;
	t_env				*env;

	env = (t_env*)param;
	limit = SCREENX * (env->line_id + env->offset);
	if (limit >= SCREEN)
		limit = SCREEN - 1;
	pos = env->line_id * SCREENX + (env->offset == PIX ? 0 : env->offset);
	env->line_id += env->offset;
	ray.o = env->cam.pos;
	while (pos < limit)
	{
		ray.dir = rt_get_vecdir(env->cam, pos % SCREENX, pos / SCREENX);
		color = rt_viewdir_inter(env, ray);
		rt_add_pixel(env, color, pos);
		if (env->offset >= PIX / 2)
			pos += PIX;
		else
			pos += env->offset * 2;
	}
	return (env);
}

void					rt_thread(void *env, void *(func)(void*))
{
	pthread_t			id[NBR_THREAD];
	int					i;

	i = -1;
	while (++i < NBR_THREAD)
		pthread_create(&id[i], NULL, func, env);
	i = -1;
	while (++i < NBR_THREAD)
		pthread_join(id[i], NULL);
}

int						rt_print(void *param)
{
	int					pos;
	t_env				*env;

	env = (t_env*)param;
	if (env->offset)
	{
		pos = 0;
		while (pos < SCREEN)
		{
			rt_thread((void*)env, rt_print_line);
			pos += SCREENX * NBR_THREAD * env->offset;
		}
		if (!env->key_repeat)
			env->offset /= 2;
		mlx_put_image_to_window(env->mlx.mlx, env->mlx.id,
				env->mlx.image, 0, 0);
		env->line_id = 0;
		return (rt_antialiasing(env));
	}
	return (rt_antialiasing(env));
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_texture.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoussa <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/25 18:25:07 by mmoussa           #+#    #+#             */
/*   Updated: 2019/06/25 18:25:09 by mmoussa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "rt.h"
#include "mlx.h"
#include <fcntl.h>

char			*rt_tpathname(t_env *env, int i)
{
	static int		ttext[NBR_TEXT - 3] = {TBRICK, TMARBLE, TDEARTH,
		TNEARTH, TJUPITER, TSTARS, TSNOW, TROCK, TWOOD, TPLOT, TBLUR};
	static char		*path[NBR_TEXT - 3] = {"textures/natural/brick.xpm",
		"textures/natural/marble.xpm", "textures/planet/day_earth.xpm",
		"textures/planet/night_earth.xpm", "textures/planet/jupiter.xpm",
		"textures/planet/stars.xpm", "textures/background/snow.xpm",
		"textures/natural/rock.xpm", "textures/natural/wood.xpm",
		"textures/natural/plot.xpm", "textures/natural/blur.xpm"};
	int				j;

	j = -1;
	while (++j < NBR_TEXT - 3)
		if (env->form[i].texture.type == ttext[j])
			return (path[j]);
	return (NULL);
}

void			rt_load_texture(t_env *env, int i)
{
	int				fd;
	char			*pathname;

	if (!(pathname = rt_tpathname(env, i)) ||
		(fd = open(pathname, O_RDONLY)) < 0)
	{
		ft_putendl(pathname);
		ft_putstr_fd("rt: can not read texture\n", 2);
		env->form[i].color = (t_vector) {1, 0, 1};
		env->form[i].texture.type = TCHECKER;
		return ;
	}
	env->form[i].timage.buffer = mlx_xpm_file_to_image(env->mlx.mlx,
		pathname, &env->form[i].timage.width,
		&env->form[i].timage.height);
	env->form[i].timage.buffer_ptr = mlx_get_data_addr(
		env->form[i].timage.buffer, &env->mlx.pix, &env->mlx.size_line,
		&env->mlx.endian);
}

void			rt_init_texture(t_env *env)
{
	int				i;

	i = -1;
	while (++i < env->nbr_form)
		if (env->form[i].texture.type != TCHECKER
			&& env->form[i].texture.type != TPERLIN
			&& env->form[i].texture.type != TNOTHING)
			rt_load_texture(env, i);
}

void			rt_get_texture(t_env *env, t_texture texture, t_vector normal,
	t_inter *inter)
{
	if (texture.type == TCHECKER)
		inter->color = ft_vadd(inter->color,
			(rt_tchecker(normal, inter->color, env, inter)));
	else if (texture.type == TPERLIN)
		inter->color = ft_vadd(inter->color,
			(rt_tperlin(normal, inter->color, env, inter)));
	else if (texture.type != TNOTHING)
		inter->color = rt_tmap(normal, inter->color, env, inter);
}

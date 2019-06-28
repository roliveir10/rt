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

void	rt_load_texture(t_env *env, int i)
{
	env->form[i].timage.buffer = mlx_xpm_file_to_image(env->mlx.mlx, "textures/brick.xpm", &env->form[i].timage.width, &env->form[i].timage.height);
	// ft_putendlnb(env->form[i].timage.width);
	env->form[i].timage.buffer_ptr = mlx_get_data_addr(env->form[i].timage.buffer, &env->mlx.pix, &env->mlx.size_line, &env->mlx.endian);
/*				getcolor(env->form[i].timage, 5, 5);
**		mlx_put_image_to_window(env->mlx.mlx, env->mlx.id, env->form[i].timage.buffer, 0, 0);
*/
}

void			rt_init_texture(t_env *env)
{
	int		i;

	i = -1;
	while (++i < env->nbr_form)
	{
		rt_load_texture(env, i);
	}
}

void			rt_get_texture(t_env *env, t_texture texture, t_vector normal, t_inter *inter)
{
	static int		ttext[NBR_TEXT - 1] = {TCHECKER, TMAP, TPERLIN};
	static t_vector	(*func[NBR_TEXT - 1])(t_vector, t_vector, t_env*,
		t_inter*) = {rt_tchecker, rt_tmap, rt_tperlin};
	int				i;

	i = 3;
	while (--i + 1)
		normal = ft_vrotate(normal, env->form[inter->id].mat[i]);
	while (++i < NBR_TEXT - 1)
	{
		if (texture.type == ttext[i])
			inter->color = ft_vadd(inter->color,
				(func[i](normal, inter->color, env, inter)));
	}
}

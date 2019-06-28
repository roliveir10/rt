/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_texture_map.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoussa <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/26 18:02:56 by mmoussa           #+#    #+#             */
/*   Updated: 2019/06/26 18:02:59 by mmoussa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <fcntl.h>
#include "mlx.h"
#include "rt.h"
#include <unistd.h>

int		getcolor(t_timage img, int x, int y)
{
	int	color;
	int	c;

	c = (y * img.width + x) * 4;
	color = img.buffer_ptr[c];
	if (color == -120 && img.buffer_ptr[c + 1] == 0 && img.buffer_ptr[c + 2] == -104)
		return (256 * 256 * 256 + 256 * 256 + 256);
	color += img.buffer_ptr[c + 1] * 256;
	color += img.buffer_ptr[c + 2] * 256 * 256;
	printf("%x\n", color);
	return (color);
}

t_vector			rt_tmap(t_vector normal, t_vector intercolor, t_env *env,
						t_inter *inter)
{
	// static int		tftype[NBR_FORM] = {SPHERE, PLAN, CYLINDRE, CONE};
	// static t_vector	(*func[NBR_FORM])(t_vector, t_vector, t_inter*,
	// 	t_form*) = {rt_map_sphere, rt_map_plan,
	// 	rt_map_cylindre, rt_map_cone};

	(void)normal;
	(void)env;
	(void)intercolor;
	(void)inter;

	static int i = 0;
	i++;
	// int			x;
	// int			y;
	// env->form[inter->id].timage = 
	
	
	
	// xpm = mlx_new_image(env->mlx.mlx, SCREENX, SCREENY);
	// ft_putstr(xpm);
	if (i == 1 && (env->form[inter->id].timage.buffer = mlx_xpm_file_to_image(env->mlx.mlx, "textures/brick.xpm", &(env->form[inter->id].timage.width), &(env->form[inter->id].timage.height))))
	{
		// ft_putnbr(height);
		// ft_putstr(" | ");
		// ft_putnbr(height);
		// ft_putstr(" | ");
		// ft_putstr(env->form[inter->id].timage);
		// ft_putstr("\n");
		// getcolor(env->form[inter->id].timage, 1, 100);
		env->form[inter->id].timage.buffer_ptr = mlx_get_data_addr(env->form[inter->id].timage.buffer, &(env->mlx.pix), &(env->mlx.size_line), &(env->mlx.endian));
		
		// y = -1;
		// while (y < env->form[inter->id].timage.height)
		// {
		// 	x = -1;
		// 	while (x < env->form[inter->id].timage.width)
		// 	{
				getcolor(env->form[inter->id].timage, 10, 10);
		// 	}
		// }
		mlx_put_image_to_window(env->mlx.mlx, env->mlx.id, env->form[inter->id].timage.buffer, 0, 0);
	}
	
	// mlx_destroy_image(env->mlx.mlx, xpm);
	// ft_putendl(env->form[inter->id].timage->buffer);
	// printf("%d\n", );
	// int				i;

	// i = -1;
	// while (++i < NBR_FORM)
	// {
	// 	if (form->ftype == tftype[i])
	// 		intercolor = func[i](normal, intercolor, inter, form);
	// }
	return (intercolor);
}

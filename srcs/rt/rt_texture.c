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

void			rt_get_texture(t_texture texture, t_vector normal, t_form *form,
	t_inter *inter)
{
	static int		ttext[2] = {TCHECKER};
	static t_vector	(*func[2])(t_vector, t_vector, t_form*,
		t_inter*) = {rt_tchecker};
	int				i;

	i = 3;
	while (--i + 1)
		normal = ft_vrotate(normal, form->mat[i]);
	while (++i < 2)
	{
		if (texture.type == ttext[i])
			inter->color = ft_vadd(inter->color,
				(func[i](normal, inter->color, form, inter)));
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_loading.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atelli <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/01 15:51:20 by atelli            #+#    #+#             */
/*   Updated: 2019/07/01 15:51:23 by atelli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include <mlx.h>

int			rt_loading(int i, t_env *env, int b)
{
	if (b == 0)
	{
		if (env->key_repeat)
		{
			ft_bzero(env->mlx.mem_image, sizeof(env->mlx.mem_image));
			i = 0;
		}
		if (env->line_id > SCREENY)
		{
			env->line_id = 0;
			if (!env->key_repeat)
				env->offset /= 2;
		}
	}
	if (b == 1)
	{
		i++;
		if (i >= (SCREENY / 2) - 32)
			i = (SCREENY / 2) - 32;
	}
	return (i);
}

char		*rt_loading1(int i)
{
	char		*test;
	char		*lol;
	char		*loading;

	test = ft_itoa(i * 100 / ((SCREENY / 2) - 32));
	lol = ft_strjoin("Loading : ", test);
	loading = ft_strjoin(lol, "%");
	ft_strdel(&test);
	ft_strdel(&lol);
	return (loading);
}

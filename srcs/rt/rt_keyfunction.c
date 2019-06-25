/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_keyfunction.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roliveir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/24 02:33:12 by roliveir          #+#    #+#             */
/*   Updated: 2019/06/24 02:53:07 by roliveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void			rt_escap(t_env *env, int keycode)
{
	(void)keycode;
	rt_delenv(env);
}

void			rt_aa_blinn(t_env *env, int keycode)
{
	if (keycode == KAA)
		env->scene.aa = env->scene.aa ? 0 : 1;
	else if (keycode == KBLINN)
	{
		env->key_repeat = 1;
		env->scene.blinn = env->scene.blinn ? 0 : 1;
		env->offset = PIX;
	}
}

int				rt_close(void *param)
{
	rt_delenv((t_env*)param);
	return (1);
}

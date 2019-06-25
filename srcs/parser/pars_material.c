/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_material.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutrol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/19 16:55:27 by oboutrol          #+#    #+#             */
/*   Updated: 2019/06/23 16:22:46 by oboutrol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pars.h"

t_material		pars_material(t_token **token, t_env *env)
{
	t_material	mat;
	char		*word;

	ft_bzero(&mat, sizeof(t_material));
	if (!(word = (*token)->word))
		return (mat);
	if (!ft_strcmp("\"nothing\"", word))
		mat = rt_get_material(NOTHING, env->scene);
	else if (!ft_strcmp("\"jade\"", word))
		mat = rt_get_material(JADE, env->scene);
	free_move(token);
	return (mat);
}

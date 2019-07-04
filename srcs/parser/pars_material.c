/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_material.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutrol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/19 16:55:27 by oboutrol          #+#    #+#             */
/*   Updated: 2019/06/26 11:22:04 by oboutrol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pars.h"

t_material		pars_material(t_token **token, t_env *env)
{
	t_material	mat;
	char		*word;
	int			k;
	static char	*materials[NBR_MATERIAL + 1] = {"\"nothing\"", "\"emerald\"",
		"\"jade\"", "\"obsidian\"", "\"pearl\"", "\"ruby\"", "\"turquoise\"",
		"\"brass\"", "\"bronze\"", "\"chrome\"", "\"copper\"", "\"gold\"",
		"\"silver\""};

	ft_bzero(&mat, sizeof(t_material));
	if (!(word = (*token)->word))
		return (mat);
	k = -1;
	while (++k < NBR_MATERIAL + 1)
		if (!ft_strcmp(word, materials[k]))
			mat = rt_get_material(k, env->scene);
	free_move(token);
	return (mat);
}

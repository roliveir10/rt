/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_camera.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutrol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/23 02:11:36 by oboutrol          #+#    #+#             */
/*   Updated: 2019/06/25 09:16:00 by roliveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pars.h"
#include "libft.h"

int					pars_camera(t_token **token, t_env *env)
{
	int				ret;

	ret = 1;
	free_move(token);
	if (free_move(token))
		return (-1);
	if ((*token)->type == BRAO)
	{
		ft_putstr_fd("rt: Only one camera expected, remove lst\n", 2);
		return (-1);
	}
	free_move(token);
	while ((ret = pars_field_camera(token, env)) != -1)
	{
		if (!(*token) || (*token)->type != ENDED)
			break ;
		free_move(token);
	}
	free_move(token);
	return (ret);
}

int					pars_scene(t_token **token, t_env *env)
{
	int				ret;

	ret = 1;
	free_move(token);
	if (free_move(token))
		return (-1);
	if ((*token)->type == BRAO)
	{
		ft_putstr_fd("rt: Only one scene expected, remove lst\n", 2);
		return (-1);
	}
	free_move(token);
	while ((ret = pars_field_scene(token, env)) != -1)
	{
		if (!(*token) || (*token)->type != ENDED)
			break ;
		free_move(token);
	}
	free_move(token);
	return (ret);
}

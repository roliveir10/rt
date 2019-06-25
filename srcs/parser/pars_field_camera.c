/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_field_camera.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutrol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/17 16:20:16 by oboutrol          #+#    #+#             */
/*   Updated: 2019/06/25 09:17:38 by roliveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pars.h"
#include "libft.h"

static int		pars_select_field(t_token **token, t_env *env)
{
	char		*word;

	word = ft_strdup((*token)->word);
	if (!word)
		return (1);
	if (free_double_move(token))
	{
		ft_strdel(&word);
		return (1);
	}
	if (!ft_strcmp(word, "\"origin\""))
		env->cam.pos = pars_vector(token);
	else if (!ft_strcmp(word, "\"rotation\""))
		env->cam.rotation = pars_vector(token);
	else
	{
		ft_putstr_fd("rt: invalid field: ", 2);
		ft_putstr_fd(word, 2);
		ft_putstr_fd(" in type `camera'\n", 2);
		ft_strdel(&word);
		return (1);
	}
	ft_strdel(&word);
	return (0);
}

int				pars_field_camera(t_token **token, t_env *env)
{
	if ((*token)->type != NAMES)
	{
		ft_putstr_fd("rt: wrong format for camera definition\n", 2);
		return (-1);
	}
	if (pars_select_field(token, env))
		return (-1);
	return (1);
}

static int		pars_select_field_scene(t_token **token, t_env *env)
{
	char		*word;

	word = ft_strdup((*token)->word);
	if (!word)
		return (1);
	if (free_double_move(token))
	{
		ft_strdel(&word);
		return (1);
	}
	if (!ft_strcmp(word, "\"ambient\""))
		env->scene.ambient = pars_double(token);
	else if (!ft_strcmp(word, "\"specular\""))
		env->scene.spec = pars_double(token);
	else
	{
		ft_putstr_fd("rt: invalid field: ", 2);
		ft_putstr_fd(word, 2);
		ft_putstr_fd(" in type `scene'\n", 2);
		ft_strdel(&word);
		return (1);
	}
	ft_strdel(&word);
	return (0);
}

int				pars_field_scene(t_token **token, t_env *env)
{
	if ((*token)->type != NAMES)
	{
		ft_putstr_fd("rt: wrong format for scene definition\n", 2);
		return (-1);
	}
	if (pars_select_field_scene(token, env))
		return (-1);
	return (1);
}

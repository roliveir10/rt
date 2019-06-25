/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_type.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutrol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/16 19:49:55 by oboutrol          #+#    #+#             */
/*   Updated: 2019/06/24 13:57:09 by oboutrol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pars.h"
#include "libft.h"

t_form				pars_one_form(t_token **token, t_env *env)
{
	t_form			form;

	ft_bzero(&form, sizeof(t_form));
	env->scene.spec = 0.316;
	form.material = rt_get_material(NOTHING, env->scene);
	free_move(token);
	while (pars_field_form(token, &form, env) != -1)
	{
		if (!(*token) || (*token)->type != ENDED)
			break ;
		free_move(token);
	}
	free_move(token);
	return (form);
}

int					pars_object(t_token **token, t_env *env)
{
	t_form			form;
	t_lstform		*lstform;

	lstform = NULL;
	free_move(token);
	free_move(token);
	if ((*token)->type == BRAO)
	{
		free_move(token);
		while (1)
		{
			form = pars_one_form(token, env);
			add_form(&lstform, form);
			if (!(*token) || (*token)->type != ENDED)
				break ;
			free_move(token);
		}
		free_move(token);
	}
	else
		pars_one_form(token, env);
	env->nbr_form = size_lst_form(lstform);
	env->form = lstform_to_form(lstform, env->nbr_form);
	return (1);
}

t_lum				pars_one_light(t_token **token)
{
	t_lum			light;

	ft_bzero(&light, sizeof(t_lum));
	light.constant = 1.0;
	light.quadratic = 0.045;
	light.linear = 0.009;
	free_move(token);
	while (pars_field_light(token, &light) != -1)
	{
		if (!(*token) || (*token)->type != ENDED)
			break ;
		free_move(token);
	}
	free_move(token);
	return (light);
}

int					pars_light(t_token **token, t_env *env)
{
	t_lum			light;
	t_lstlum		*lstlum;

	lstlum = NULL;
	free_move(token);
	free_move(token);
	if ((*token)->type == BRAO)
	{
		free_move(token);
		while (1)
		{
			light = pars_one_light(token);
			add_light(&lstlum, light);
			if (!(*token) || (*token)->type != ENDED)
				break ;
			free_move(token);
		}
		free_move(token);
	}
	else
		pars_one_light(token);
	env->nbr_lum = size_lst(lstlum);
	env->lum = lstlum_to_lum(lstlum, env->nbr_lum);
	return (1);
}

int					pars_type(t_token **token, t_env *env)
{
	int				k;
	static char		*types[NB_TYPES] = {"\"camera\"", "\"object\"",
		"\"light\"", "\"scene\""};
	static int		(*fct_pars[NB_TYPES])(t_token**, t_env*) = {
		pars_camera, pars_object, pars_light, pars_scene};

	if (!(*token) || !(*token)->word)
		return (-1);
	k = -1;
	while (++k < NB_TYPES)
		if (!ft_strcmp(types[k], (*token)->word))
			return ((fct_pars[k])(token, env));
	return (-1);
}

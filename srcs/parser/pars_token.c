/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutrol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/16 17:12:49 by oboutrol          #+#    #+#             */
/*   Updated: 2019/06/25 09:18:27 by roliveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pars.h"

t_env		error_start(t_env env, int *err)
{
	ft_putstr_fd("rt: JSON file should start with `{'\n", 2);
	*err = 1;
	return (env);
}

t_env		token_to_env(t_token **token, int *err)
{
	t_env	env;
	int		ret;

	ret = 1;
	ft_bzero(&env, sizeof(t_env));
	pars_fill_cam(&env.cam);
	env.scene.spec = 0.5;
	env.scene.ambient = 0.1;
	if (!token || !(*token))
		return (env);
	if ((*token)->type != CBRO)
		error_start(env, err);
	free_move(token);
	while ((ret = pars_type(token, &env)))
	{
		if (ret == -1)
		{
			*err = 1;
			return (env);
		}
		if (!(*token) || (*token)->type != ENDED)
			return (env);
		free_move(token);
	}
	return (env);
}

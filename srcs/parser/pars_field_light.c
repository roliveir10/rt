/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_field_light.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutrol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/17 20:35:34 by oboutrol          #+#    #+#             */
/*   Updated: 2019/06/25 09:17:54 by roliveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pars.h"
#include "libft.h"

static int		pars_name_light(t_token **token)
{
	int			type;
	char		*word;

	type = 0;
	if (!(word = (*token)->word))
		return (0);
	if (!ft_strcmp(word, "\"spot\""))
		type = LSPOT;
	else if (!ft_strcmp(word, "\"cast\""))
		type = LCAST;
	else if (!ft_strcmp(word, "\"point\""))
		type = LPOINT;
	free_move(token);
	return (type);
}

static int		following(t_token **token, t_lum *light, char *word)
{
	if (!ft_strcmp(word, "\"quadratic\""))
		light->quadratic = pars_double(token);
	else if (!ft_strcmp(word, "\"type\""))
		light->type = pars_name_light(token);
	else
	{
		ft_putstr_fd("rt: invalid field: ", 2);
		ft_putstr_fd(word, 2);
		ft_putstr_fd(" in type `light'\n", 2);
		return (1);
	}
	return (0);
}

static int		pars_select_field(t_token **token, t_lum *light)
{
	char		*word;
	int			ret;

	ret = 0;
	word = ft_strdup((*token)->word);
	if (!word)
		return (1);
	if (free_move(token))
		return (1);
	if (free_move(token))
		return (1);
	if (!ft_strcmp(word, "\"origin\""))
		light->pos = pars_vector(token);
	else if (!ft_strcmp(word, "\"color\""))
		light->color = pars_vector_color(token);
	else if (!ft_strcmp(word, "\"direct\""))
		light->dir = pars_vector(token);
	else if (!ft_strcmp(word, "\"linear\""))
		light->linear = pars_double(token);
	else
		ret = following(token, light, word);
	ft_strdel(&word);
	return (ret);
}

int				pars_field_light(t_token **token, t_lum *light)
{
	if ((*token)->type != NAMES)
	{
		ft_putstr_fd("rt: wrong format for light definition\n", 2);
		return (-1);
	}
	if (pars_select_field(token, light))
		return (-1);
	return (0);
}

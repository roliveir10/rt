/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_field_form.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutrol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/18 00:14:42 by oboutrol          #+#    #+#             */
/*   Updated: 2019/06/25 09:17:23 by roliveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pars.h"
#include "libft.h"

static int		following(t_form *form, char *word, t_token **token, t_env *env)
{
	if (!ft_strcmp(word, "\"rotation\""))
		form->rotation = pars_vector(token);
	else if (!ft_strcmp(word, "\"name\""))
		form->ftype = pars_name(token);
	else if (!ft_strcmp(word, "\"direct\""))
		form->direct = pars_vector(token);
	else if (!ft_strcmp(word, "\"point\""))
		form->point = pars_vector(token);
	else if (!ft_strcmp(word, "\"material\""))
		form->material = pars_material(token, env);
	else
	{
		ft_putstr_fd("rt: invalid field: ", 2);
		ft_putstr_fd(word, 2);
		ft_putstr_fd(" in type `form'\n", 2);
		return (-1);
	}
	return (0);
}

static int		pars_select_field(t_token **token, t_form *form, t_env *env)
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
		form->center = pars_vector(token);
	else if (!ft_strcmp(word, "\"color\""))
		form->color = pars_vector_color(token);
	else if (!ft_strcmp(word, "\"rayon\""))
		form->r = pars_double(token);
	else if (!ft_strcmp(word, "\"height\""))
		form->h = pars_double(token);
	else if (!ft_strcmp(word, "\"angle\""))
		form->angle = pars_double(token);
	else
		ret = following(form, word, token, env);
	ft_strdel(&word);
	return (ret);
}

int				pars_field_form(t_token **token, t_form *form, t_env *env)
{
	if ((*token)->type != NAMES)
	{
		ft_putstr_fd("rt: wrong format for form definition\n", 2);
		return (-1);
	}
	if (pars_select_field(token, form, env))
		return (-1);
	return (0);
}

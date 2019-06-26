/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_field_light.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutrol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/17 20:35:34 by oboutrol          #+#    #+#             */
/*   Updated: 2019/06/26 13:36:47 by oboutrol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pars.h"
#include "libft.h"

int				pars_name_light(t_token **token)
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

static int		pars_select_field(t_token **token, t_lum *light)
{
	char			*word;
	int				k;
	static char		*names[NB_FIELDS_LUM] = {
		"\"origin\"", "\"direct\"", "\"color\"", "\"type\"", "\"intensity\"",
		"\"cutoff\""};
	static void		*(*fct_set[NB_FIELDS])(t_lum*, t_token**) = {
		set_origin_lum, set_direct_lum, set_color_lum, set_type_lum,
		set_intensity_lum, set_cutoff_lum};

	k = -1;
	word = ft_strdup((*token)->word);
	if (!word)
		return (1);
	free_double_move(token);
	while (++k < NB_FIELDS_LUM)
		if (!ft_strcmp(names[k], word))
		{
			fct_set[k](light, token);
			ft_strdel(&word);
			return (0);
		}
	ft_putstr_fd("rt: invalid field: ", 2);
	ft_putstr_fd(word, 2);
	ft_putstr_fd(" in type `light'\n", 2);
	ft_strdel(&word);
	return (1);
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

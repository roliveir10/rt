/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_field_form.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutrol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/18 00:14:42 by oboutrol          #+#    #+#             */
/*   Updated: 2019/07/10 15:02:32 by oboutrol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pars.h"
#include "libft.h"

static int		following(t_form *form, char *word, t_token **token, t_env *env)
{
	if (!ft_strcmp(word, "\"material\""))
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
	char			*word;
	int				ret;
	int				k;
	static char		*names[NB_FIELDS] = {
		"\"origin\"", "\"color\"", "\"rotation\"", "\"direct\"", "\"point\"",
		"\"radius\"", "\"height\"", "\"angle\"", "\"name\"", "\"texture\"",
		"\"atexture\"", "\"scale\"", "\"tilscolor\"", "\"reflection\"",
		"\"max\"", "\"min\"", "\"transp\"", "\"density\""};
	static void		*(*fct_set[NB_FIELDS])(t_form*, t_token**) = {
		set_origin_form, set_color_form, set_rotation_form, set_direct_form,
		set_point_form, set_radius_form, set_height_form, set_angle_form,
		set_name_form, set_texture_form, set_atexture_form,
		set_scale_form, set_tcolor_form, set_reflection_form, set_max_form,
		set_min_form, set_transp_form, set_density_form};

	if (!(word = ft_strdup((*token)->word)))
		return (1);
	free_double_move(token);
	k = -1;
	ret = 1;
	while (++k < NB_FIELDS)
		if (!ft_strcmp(names[k], word) && !(ret = 0))
			fct_set[k](form, token);
	if (ret)
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

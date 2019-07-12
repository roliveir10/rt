/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_form_limit.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutrol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/12 13:58:15 by oboutrol          #+#    #+#             */
/*   Updated: 2019/07/12 13:58:54 by oboutrol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pars.h"
#include "libft.h"

void		*set_max_form(t_form *form, t_token **token)
{
	form->max = pars_vector(token);
	if (form->fields[MAX])
		print_warning("redifinition of Max field");
	form->fields[MAX] = 1;
	return (NULL);
}

void		*set_min_form(t_form *form, t_token **token)
{
	form->min = pars_vector(token);
	if (form->fields[MIN])
		print_warning("redifinition of Min field");
	form->fields[MIN] = 1;
	return (NULL);
}

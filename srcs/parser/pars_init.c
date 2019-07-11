/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutrol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/10 19:11:34 by oboutrol          #+#    #+#             */
/*   Updated: 2019/07/11 19:09:18 by oboutrol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pars.h"
#include "rt.h"
#include "libft.h"

void		init_form(t_form *form, int size)
{
	ft_bzero(form, size);
	form->texture.scale = 10;
	form->texture.pfrequ = 5;
	form->texture.pdepth = 4;
	form->texture.bfrequ = 1;
	form->texture.bdepth = 0.1;
	form->ftype = NOTAFORM;
}

t_token		*lex_init_token(int type, char *str)
{
	t_token	*token;

	if (!(token = (t_token*)ft_memalloc(sizeof(t_token))))
		return (NULL);
	if (str)
		token->word = ft_strdup(str);
	token->type = type;
	return (token);
}

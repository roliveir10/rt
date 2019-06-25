/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutrol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/10 19:11:34 by oboutrol          #+#    #+#             */
/*   Updated: 2019/06/11 23:49:47 by oboutrol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pars.h"
#include "rt.h"
#include "libft.h"

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

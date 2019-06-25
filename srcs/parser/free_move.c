/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_move.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutrol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/23 03:48:17 by oboutrol          #+#    #+#             */
/*   Updated: 2019/06/25 09:15:17 by roliveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pars.h"
#include <stdlib.h>

int				free_move(t_token **token)
{
	t_token		*tmp;

	if (!token || !(*token))
	{
		ft_putstr_fd("rt: unexpected end of file\n", 2);
		exit(1);
	}
	tmp = *token;
	if (!(*token = (*token)->next))
	{
		ft_putstr_fd("rt: unexpected end of file\n", 2);
		exit(1);
	}
	ft_strdel(&tmp->word);
	free(tmp);
	return (0);
}

int				free_double_move(t_token **token)
{
	if (free_move(token) || free_move(token))
		return (1);
	return (0);
}

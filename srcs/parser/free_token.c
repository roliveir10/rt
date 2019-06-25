/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutrol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/23 02:28:55 by oboutrol          #+#    #+#             */
/*   Updated: 2019/06/24 10:47:17 by oboutrol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pars.h"
#include <stdlib.h>

void		free_token(t_token **token)
{
	if (!token || !(*token))
		return ;
	if ((*token)->next)
		free_token(&(*token)->next);
	if ((*token)->word)
		ft_strdel(&(*token)->word);
	free(*token);
	*token = NULL;
}

void		free_lstform(t_lstform **lstform)
{
	if (!(*lstform))
		return ;
	free_lstform(&(*lstform)->next);
	free(*lstform);
}

void		free_lstlum(t_lstlum **lstlum)
{
	if (!(*lstlum))
		return ;
	free_lstlum(&(*lstlum)->next);
	free(*lstlum);
}

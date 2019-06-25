/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_pile.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutrol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/12 02:01:44 by oboutrol          #+#    #+#             */
/*   Updated: 2019/06/23 03:27:36 by oboutrol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pars.h"
#include <stdlib.h>

int			pile_last(t_stat *stat)
{
	t_pile	*pile;

	pile = stat->pile;
	while (pile && pile->next)
		pile = pile->next;
	if (!pile)
		return (START);
	return (pile->type);
}

static int	pile_remove(t_stat *stat)
{
	t_pile	*tmp;

	tmp = stat->pile;
	if (!tmp->next)
	{
		free(stat->pile);
		stat->pile = NULL;
	}
	else
	{
		while (tmp && tmp->next && tmp->next->next)
			tmp = tmp->next;
		free(tmp->next);
		tmp->next = NULL;
	}
	stat->status = ENDED;
	return (0);
}

void		pile_up(t_stat *stat, int type)
{
	t_pile	*tmp;
	t_pile	*new;

	if (!(new = (t_pile*)ft_memalloc(sizeof(t_pile))))
		return ;
	new->type = type;
	if (!stat->pile)
		stat->pile = new;
	else
	{
		tmp = stat->pile;
		while (tmp && tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}

int			pile_down(t_stat *stat, int type)
{
	t_pile	*tmp;

	tmp = stat->pile;
	while (tmp && tmp->next)
		tmp = tmp->next;
	if (!tmp)
		return (1);
	if (type == CBRC && tmp->type == CBRO)
		return (pile_remove(stat));
	if (type == BRAC && tmp->type == BRAO)
		return (pile_remove(stat));
	return (1);
}

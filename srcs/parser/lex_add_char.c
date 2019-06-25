/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_add_char.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutrol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/09 15:02:48 by oboutrol          #+#    #+#             */
/*   Updated: 2019/06/18 00:57:33 by oboutrol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pars.h"
#include <stdlib.h>
#include "libft.h"

static int	size_pile(t_pile *pile)
{
	t_pile	*tmp;
	int		k;

	k = 0;
	tmp = pile;
	while (tmp)
	{
		tmp = tmp->next;
		k++;
	}
	return (k);
}

void		re_type(int *type, char *word)
{
	int		k;

	if (!word)
		return ;
	k = get_type(word[0]);
	if (k > 2 && k < 7)
		*type = k;
}

void		lex_add_token(char buff[BUFF], t_stat *stat, t_token *token)
{
	t_token	*tmp;
	t_token	*new;

	tmp = token;
	while (tmp->next)
		tmp = tmp->next;
	if (!(new = lex_init_token(0, NULL)))
		return ;
	tmp->next = new;
	if (stat->load)
		new->word = ft_strjoin(stat->load, buff);
	else
		new->word = ft_strdup(buff);
	new->next = NULL;
	new->type = stat->old_status;
	re_type(&new->type, new->word);
	new->pile = size_pile(stat->pile);
	buff[0] = '\0';
}

void		lex_add_char(char buff[BUFF], char **load, char cha)
{
	int		size;
	char	*tmp;

	size = ft_strlen(buff);
	if (size >= BUFF - 1)
	{
		if (!(*load))
			*load = ft_strdup(buff);
		else
		{
			tmp = *load;
			*load = ft_strjoin(*load, buff);
			free(tmp);
		}
		ft_bzero(buff, BUFF);
		buff[0] = cha;
	}
	else
	{
		buff[size] = cha;
		buff[size + 1] = 0;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_lst_form.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutrol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/17 23:39:23 by oboutrol          #+#    #+#             */
/*   Updated: 2019/06/23 17:09:30 by oboutrol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pars.h"

int				size_lst_form(t_lstform *tmp)
{
	int			k;

	k = 0;
	while (tmp)
	{
		tmp = tmp->next;
		k++;
	}
	return (k);
}

t_form			*lstform_to_form(t_lstform *lstform, int size)
{
	t_form		*form;
	int			j;
	t_lstform	*tmp;

	tmp = lstform;
	if (!(form = (t_form*)ft_memalloc(sizeof(t_form) * size)))
	{
		free_lstform(&lstform);
		return (NULL);
	}
	j = -1;
	while (++j < size)
	{
		form[j] = lstform->form;
		lstform = lstform->next;
	}
	free_lstform(&tmp);
	return (form);
}

t_lstform		*new_form(t_form form)
{
	t_lstform	*new;

	if (!(new = (t_lstform*)ft_memalloc(sizeof(t_lstform))))
		return (NULL);
	new->form = form;
	return (new);
}

void			add_form(t_lstform **lstform, t_form form)
{
	t_lstform	*tmp;

	if (!*lstform)
		*lstform = new_form(form);
	else
	{
		tmp = *lstform;
		while (tmp && tmp->next)
			tmp = tmp->next;
		tmp->next = new_form(form);
	}
}

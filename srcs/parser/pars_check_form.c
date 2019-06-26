/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_check_form.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutrol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/26 02:35:09 by oboutrol          #+#    #+#             */
/*   Updated: 2019/06/26 06:14:43 by oboutrol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "pars.h"

int		print_no_field(char *field, char *elmt, char *type)
{
	ft_putstr_fd("Undefine necessary field `", 2);
	ft_putstr_fd(field, 2);
	ft_putstr_fd("' in ", 2);
	ft_putstr_fd(type, 2);
	ft_putstr_fd(" `", 2);
	ft_putstr_fd(elmt, 2);
	ft_putstr_fd("'\n", 2);
	return (1);
}

char	*get_name(int k)
{
	static char	*names[NBR_FORM] = {"Sphere", "Plan", "Cylindre", "Cone"};

	if (k < 0 || k >= NBR_FORM)
		return ("Undefine Form");
	return (names[k]);
}

char	*get_field(int k)
{
	static char	*names[NB_FIELDS] = {"name", "origin", "point", "direct",
		"radius", "height", "angle", "color", "rotation"};	

	if (k < 0 || k >= NB_FIELDS)
		return ("NOTAFIELD");
	return (names[k]);
}

int		pars_check_form(t_form form)
{
	int			k;
	int			ret;
	static int	mat[NBR_FORM][NB_FIELDS] = {
		{SPHERE, 1, 0, 0, 1, 0, 0, 1, 2},
		{PLAN, 1, 0, 0, 0, 0, 0, 1, 2},
		{CYLINDRE, 1, 0, 0, 1, 0, 0, 1, 2},
		{CONE, 1, 0, 0, 0, 0, 1, 1, 2}};

	k = 0;
	ret = 0;
	while (++k < NB_FIELDS)
	{
		if (!form.fields[k] && mat[form.ftype][k] == 1)
			ret = print_no_field(get_field(k), get_name(form.ftype), "form");
	}
	if (ret)
		ft_putstr_fd("rt: Warning: Dropping form\n", 2);
	return (ret);
}

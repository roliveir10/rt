/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_check_form.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutrol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/26 02:35:09 by oboutrol          #+#    #+#             */
/*   Updated: 2019/07/12 14:04:27 by oboutrol         ###   ########.fr       */
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
	static char	*names[NBR_FORM] = {"Sphere", "Plan", "Cylindre", "Cone",
		"Torus", "Hyperbol", "cubetroue", "verre", "cube"};

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
	static int	mat[4][NB_FIELDS] = {
		{SPHERE, 3, NAME, ORIGIN, RADIUS},
		{PLAN, 2, NAME, ORIGIN},
		{CYLINDRE, 3, NAME, ORIGIN, RADIUS},
		{CONE, 3, NAME, ORIGIN, ANGLE}};

	k = 1;
	ret = 0;
	if (!form.fields[NAME])
		return (print_no_field("name", "undefine", "form"));
	if (form.ftype > 3)
		return (0);
	while (++k < mat[form.ftype][1] + 2)
	{
		if (!form.fields[mat[form.ftype][k]])
			ret = print_no_field(get_field(mat[form.ftype][k]),
					get_name(form.ftype), "form");
	}
	if (ret)
		ft_putstr_fd("rt: Warning: Dropping form\n", 2);
	return (ret);
}

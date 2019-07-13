/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_4th_deg.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutrol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/02 15:03:59 by oboutrol          #+#    #+#             */
/*   Updated: 2019/07/13 09:45:23 by oboutrol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "rt.h"
#include <math.h>

static double	valid_small(double r1, double r2)
{
	if (r1 < 0 && r2 < 0)
		return (-1);
	if (r1 >= 0 && r2 >= 0)
	{
		if (r1 < r2)
			return (r1);
		else
			return (r2);
	}
	if (r1 > 0)
		return (r1);
	else
		return (r2);
}

static double	valid_smallt(double r1, double r2, double r3, double r4)
{
	r1 = valid_small(r1, r2);
	r1 = valid_small(r1, r3);
	r1 = valid_small(r1, r4);
	return (r1);
}

void			slide(double var[5])
{
	double		div;

	div = var[0];
	var[0] = var[1] / div;
	var[1] = var[2] / div;
	var[2] = var[3] / div;
	var[3] = var[4] / div;
}

double			bi_carr(double var[5])
{
	double		fact[3];
	double		res;

	fact[0] = -3 * var[0] * var[0] / 8 + var[1];
	fact[1] = pow(var[0] / 2, 3) - 0.5 * var[0] * var[1] + var[2];
	fact[2] = -3 * pow(var[0] / 4, 4) + var[1] * pow(var[0] / 4, 2)
		- 0.25 * var[0] * var[2] + var[3];
	if (fact[1] == 0)
	{
		res = ft_2nd_degree(1, fact[0], fact[2]);
		if (res >= 0)
			return (sqrt(res));
	}
	return (-1);
}

double			ft_4th_degree(double var[5])
{
	double	r[4];
	double	elmt[3];
	double	fast[3];
	double	el;

	slide(var);
	if ((el = bi_carr(var)) != -1)
		return (el);
	fast[0] = pow(var[1], 2) - 3 * var[0] * var[2] + 12 * var[3];
	fast[1] = 2 * pow(var[1], 3) - 9 * var[0] * var[1] * var[2]
		+ 27 * pow(var[2], 2) + 27 * pow(var[0], 2) * var[3]
		- 72 * var[1] * var[3];
	el = -4 * pow(fast[0], 3) + pow(fast[1], 2);
	if (el < 0)
		el = -el;
	fast[2] = fast[1] + sqrt(el);
	elmt[0] = term_a(var, fast);
	elmt[1] = term_b(var, fast);
	elmt[2] = term_c(var, fast);
	r[0] = -0.25 * var[0] - 0.5 * sqrt(elmt[0]) - 0.5 * sqrt(elmt[1] - elmt[2]);
	r[1] = -0.25 * var[0] - 0.5 * sqrt(elmt[0]) + 0.5 * sqrt(elmt[1] - elmt[2]);
	r[2] = -0.25 * var[0] + 0.5 * sqrt(elmt[0]) - 0.5 * sqrt(elmt[1] + elmt[2]);
	r[3] = -0.25 * var[0] + 0.5 * sqrt(elmt[0]) + 0.5 * sqrt(elmt[1] + elmt[2]);
	return (valid_smallt(r[0], r[1], r[2], r[3]));
}

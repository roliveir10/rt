/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_4th_deg.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutrol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/02 15:03:59 by oboutrol          #+#    #+#             */
/*   Updated: 2019/07/02 15:34:41 by oboutrol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libft.h"
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

double			term_a(double var[5], double fast[3])
{
	double		res;
	double		den;

	res = pow(var[0], 2) / 4;
	res -= 2 * var[1] / 3;
	den = 3 * cbrt(fast[2]);
	res += cbrt(2) * fast[0] / den;
	res += cbrt(fast[2] / 54);
	return (res);
}

double			term_b(double var[5], double fast[3])
{
	double		res;

	res = pow(var[0], 2) / 2 - 4 * var[1] / 3;
	res -= (cbrt(2) * fast[0] / (3 * cbrt(fast[2])));
	res -= cbrt(fast[2] / 54);
	return (res);
}

double			term_c(double var[5], double fast[3])
{
	double		res;
	double		deno;
	double		nume;

	res = -pow(var[0], 3) + 4 * var[0] * var[1] - 8 * var[2];
	deno = cbrt(2) * fast[0] / (3 * cbrt(fast[2]));
	nume = cbrt(fast[2] / 54);
	res /= 4 * sqrt(pow(var[0], 2) / 4 - 2 * var[1] / 3 + deno + nume);
	return (res);
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

double			ft_4th_degree(double var[5])
{
	double	r1;
	double	r2;
	double	r3;
	double	r4;
	double	elmt[3];
	double	fast[3];
	
	slide(var);
	fast[0] = pow(var[1], 2) - 3 * var[0] * var[2] + 12 * var[3];
	fast[1] = 2 * pow(var[1], 3) - 9 * var[0] * var[1] * var[2]
		+ 27 * pow(var[2], 2) + 27 * pow(var[0], 2) * var[3]
		- 72 * var[1] * var[3];
	fast[2] = fast[1] + sqrt(-4 * pow(fast[0], 3) + pow(fast[1], 2));
	elmt[0] = term_a(var, fast);
	elmt[1] = term_b(var, fast);
	elmt[2] = term_c(var, fast);
	r1 = -0.25 * var[0] - 0.5 * sqrt(elmt[0]) - 0.5 * sqrt(elmt[1] - elmt[2]);
	r2 = -0.25 * var[0] - 0.5 * sqrt(elmt[0]) + 0.5 * sqrt(elmt[1] - elmt[2]);
	r3 = -0.25 * var[0] + 0.5 * sqrt(elmt[0]) - 0.5 * sqrt(elmt[1] + elmt[2]);
	r4 = -0.25 * var[0] + 0.5 * sqrt(elmt[0]) + 0.5 * sqrt(elmt[1] + elmt[2]);
	return (valid_smallt(r1, r2, r3, r4));
}

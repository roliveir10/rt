/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_term.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutrol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/13 09:34:01 by oboutrol          #+#    #+#             */
/*   Updated: 2019/07/13 09:45:09 by oboutrol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "libft.h"

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

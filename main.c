/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutrol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 13:51:27 by oboutrol          #+#    #+#             */
/*   Updated: 2019/07/06 16:25:04 by oboutrol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libft/includes/libft.h"
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

double			bi_carr(double var[5])
{
	double		fact[3];
	double		a;
	double		b;

	fact[0] = -3 * var[0] * var[0] / 8 + var[1];
	fact[1] = pow(var[0] / 2 ,3) - 0.5 * var[0] * var[1] + var[2];
	fact[2] = -3 * pow(var[0] / 4 ,4) + var[1] * pow(var[0] / 4, 2)
		- 0.25 * var[0] * var[2] + var[3];
	if (fact[1] == 0)
	{
		a = fact[0];
		b = fact[2];
		return (sqrt(ft_2nd_degree(1, a, b)));
	}
	printf("%f %f %f -- les facts\n", fact[0], fact[1], fact[2]);
	return (-1);
}

double			ft_4th_degree(double var[5])
{
	double	r1;
	double	r2;
	double	r3;
	double	r4;
	double	elmt[3];
	double	fast[3];
	double	el;
	
	slide(var);//try bicarre if you can ? -> astuce pour plus de 2 first
	if ((el = bi_carr(var)) != -1)
		return (el);
	fast[0] = pow(var[1], 2) - 3 * var[0] * var[2] + 12 * var[3];
	fast[1] = 2 * pow(var[1], 3) - 9 * var[0] * var[1] * var[2]
		+ 27 * pow(var[2], 2) + 27 * pow(var[0], 2) * var[3]
		- 72 * var[1] * var[3];
//	if (-4 * pow(fast[0], 3) + pow(fast[1], 2) >= 0)
		el = -4 * pow(fast[0], 3) + pow(fast[1], 2);
//	else
//		el = 0;
	fast[2] = fast[1] + sqrt(el);
	elmt[0] = term_a(var, fast);
	elmt[1] = term_b(var, fast);
	elmt[2] = term_c(var, fast);
	r1 = -0.25 * var[0] - 0.5 * sqrt(elmt[0]) - 0.5 * sqrt(elmt[1] - elmt[2]);
	r2 = -0.25 * var[0] - 0.5 * sqrt(elmt[0]) + 0.5 * sqrt(elmt[1] - elmt[2]);
	r3 = -0.25 * var[0] + 0.5 * sqrt(elmt[0]) - 0.5 * sqrt(elmt[1] + elmt[2]);
	r4 = -0.25 * var[0] + 0.5 * sqrt(elmt[0]) + 0.5 * sqrt(elmt[1] + elmt[2]);
	printf("%f %f ses sbires ?\n", -4 * pow(fast[0], 3),  pow(fast[1], 2));
	printf("%f le mauvais ?\n", -4 * pow(fast[0], 3) + pow(fast[1], 2));
	printf("%f %f %f -- les fasts\n", fast[0], fast[1], fast[2]);
	printf("%f %f %f %f -- solutions\n", r1, r2, r3, r4);
	return (valid_smallt(r1, r2, r3, r4));
}

int		main(int argc, char **argv)
{
	double	vect[5];
	
	(void)argc;
	vect[0] = ft_atoi(argv[1]);
	vect[1] = ft_atoi(argv[2]);
	vect[2] = ft_atoi(argv[3]);
	vect[3] = ft_atoi(argv[4]);
	vect[4] = ft_atoi(argv[5]);
	printf("%f final\n", ft_4th_degree(vect));
	return (0);
}

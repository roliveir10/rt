/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_perlin3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoussa <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/08 18:05:39 by mmoussa           #+#    #+#             */
/*   Updated: 2019/07/08 18:05:40 by mmoussa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

float			rt_grad3( int hash,  float x, float y , float z ) {
	int		h;
	float	u;
	float	v;

	h = hash & 15;
	u = h < 8 ? x : y;
	v = h < 4 ? y : h == 12 || h == 14 ? x : z;
	return ((h & 1) ? -u : u) + ((h & 2) ? -v : v);
}

void			rt_init_noise3(float x, float y, float z, t_perlin *perl)
{
	perl->ix0 = rt_fastfloor(x);
	perl->iy0 = rt_fastfloor(y);
	perl->iz0 = rt_fastfloor(z);
	perl->fx0 = x - perl->ix0;
	perl->fy0 = y - perl->iy0;
	perl->fz0 = z - perl->iz0;
	perl->fx1 = perl->fx0 - 1.0f;
	perl->fy1 = perl->fy0 - 1.0f;
	perl->fz1 = perl->fz0 - 1.0f;
	perl->ix1 = (perl->ix0 + 1) & 0xff;
	perl->iy1 = (perl->iy0 + 1) & 0xff;
	perl->iz1 = (perl->iz0 + 1) & 0xff;
	perl->ix0 = perl->ix0 & 0xff;
	perl->iy0 = perl->iy0 & 0xff;
	perl->iz0 = perl->iz0 & 0xff;
	
	perl->r = rt_fade( perl->fz0 );
	perl->t = rt_fade( perl->fy0 );
	perl->s = rt_fade( perl->fx0 );
}

float			rt_noise3(float x, float y, float z)
{
	t_perlin    perl;

	rt_init_noise3(x, y, z, &perl);
	perl.nxy0 = rt_grad3(rt_perm(perl.ix0 + rt_perm(perl.iy0 + rt_perm(perl.iz0))), perl.fx0, perl.fy0, perl.fz0);
	perl.nxy1 = rt_grad3(rt_perm(perl.ix0 + rt_perm(perl.iy0 + rt_perm(perl.iz1))), perl.fx0, perl.fy0, perl.fz1);
	perl.nx0 = rt_lerp( perl.r, perl.nxy0, perl.nxy1 );
	perl.nxy0 = rt_grad3(rt_perm(perl.ix0 + rt_perm(perl.iy1 + rt_perm(perl.iz0))), perl.fx0, perl.fy1, perl.fz0);
	perl.nxy1 = rt_grad3(rt_perm(perl.ix0 + rt_perm(perl.iy1 + rt_perm(perl.iz1))), perl.fx0, perl.fy1, perl.fz1);
	perl.nx1 = rt_lerp( perl.r, perl.nxy0, perl.nxy1 );
	perl.n0 = rt_lerp( perl.t, perl.nx0, perl.nx1 );
	perl.nxy0 = rt_grad3(rt_perm(perl.ix1 + rt_perm(perl.iy0 + rt_perm(perl.iz0))), perl.fx1, perl.fy0, perl.fz0);
	perl.nxy1 = rt_grad3(rt_perm(perl.ix1 + rt_perm(perl.iy0 + rt_perm(perl.iz1))), perl.fx1, perl.fy0, perl.fz1);
	perl.nx0 = rt_lerp( perl.r, perl.nxy0, perl.nxy1 );
	perl.nxy0 = rt_grad3(rt_perm(perl.ix1 + rt_perm(perl.iy1 + rt_perm(perl.iz0))), perl.fx1, perl.fy1, perl.fz0);
	perl.nxy1 = rt_grad3(rt_perm(perl.ix1 + rt_perm(perl.iy1 + rt_perm(perl.iz1))), perl.fx1, perl.fy1, perl.fz1);
	perl.nx1 = rt_lerp(perl.r, perl.nxy0, perl.nxy1);
	perl.n1 = rt_lerp(perl.t, perl.nx0, perl.nx1);
	return (0.936f * (rt_lerp(perl.s, perl.n0, perl.n1)));
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_perlin.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoussa <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/03 11:20:59 by mmoussa           #+#    #+#             */
/*   Updated: 2019/07/03 11:21:01 by mmoussa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>

int				noise2(int x, int y)
{
	static int	seed = 0;
	static int	hash[] = {208, 34, 231, 213, 32, 248, 233, 56, 161, 78, 24,
		140, 71, 48, 140, 254, 245, 255, 247, 247, 40, 185, 248, 251, 245, 28,
		124, 204, 204, 76, 36, 1, 107, 28, 234, 163, 202, 224, 245, 128, 167,
		204, 9, 92, 217, 54, 239, 174, 173, 102, 193, 189, 190, 121, 100, 108,
		167, 44, 43, 77, 180, 204, 8, 81, 70, 223, 11, 38, 24, 254, 210, 210,
		177, 32, 81, 195, 243, 125, 8, 169, 112, 32, 97, 53, 195, 13, 203, 9,
		47, 104, 125, 117, 114, 124, 165, 203, 181, 235, 193, 206, 70, 180,
		174, 0, 167, 181, 41, 164, 30, 116, 127, 198, 245, 146, 87, 224, 149,
		206, 57, 4, 192, 210, 65, 210, 129, 240, 178, 105, 228, 108, 245,
		148, 140, 40, 35, 195, 38, 58, 65, 207, 215, 253, 65, 85, 208, 76, 62,
		3, 237, 55, 89, 232, 50, 217, 64, 244, 157, 199, 121, 252, 90, 17, 212,
		203, 149, 152, 140, 187, 234, 177, 73, 174, 193, 100, 192, 143, 97, 53,
		145, 135, 19, 103, 13, 90, 135, 151, 199, 91, 239, 247, 33, 39, 145,
		101, 120, 99, 3, 186, 86, 99, 41, 237, 203, 111, 79, 220, 135, 158, 42,
		30, 154, 120, 67, 87, 167, 135, 176, 183, 191, 253, 115, 184, 21, 233,
		58, 129, 233, 142, 39, 128, 211, 118, 137, 139, 255, 114, 20, 218,
		113, 154, 27, 127, 246, 250, 1, 8, 198, 250, 209, 92, 222, 173, 21,
		88, 102, 219};
	int			yindex;
	int			xindex;

	yindex = (y + seed) % 256;
	xindex = (hash[yindex < 0 ? yindex + 256 : yindex] + x) % 256;
	return (hash[xindex < 0 ? xindex + 256 : xindex]);
}

static float	lin_inter(float x, float y, float s)
{
	return (x + s * (y - x));
}

static float	smooth_inter(float x, float y, float s)
{
	return (lin_inter(x, y, s * s * (3 - 2 * s)));
}

static float	noise2d(float x, float y)
{
	float	xy_frac[2];
	float	xy_int[2];
	float	low;
	float	high;

	xy_int[0] = floor(x);
	xy_int[1] = floor(y);
	xy_frac[0] = x - xy_int[0];
	xy_frac[1] = y - xy_int[1];
	low = smooth_inter(noise2(xy_int[0], xy_int[1]),
		noise2(xy_int[0] + 1, xy_int[1]), xy_frac[0]);
	high = smooth_inter(noise2(xy_int[0], xy_int[1] + 1),
		noise2(xy_int[0] + 1, xy_int[1] + 1), xy_frac[0]);
	return (smooth_inter(low, high, xy_frac[1]));
}

float			perlin2d(float x, float y, float freq, int depth)
{
	float	amp;
	float	fin;
	float	div;
	int		i;

	div = 0.0;
	fin = 0;
	amp = 1.0;
	x *= freq;
	y *= freq;
	i = -1;
	while (++i < depth)
	{
		div += 256 * amp;
		fin += noise2d(x, y) * amp;
		amp /= 2;
		x *= 2;
		y *= 2;
	}
	return (fin / div);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_material_matrix.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutrol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/26 07:47:13 by oboutrol          #+#    #+#             */
/*   Updated: 2019/07/13 10:52:25 by oboutrol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int						rt_material_ambient(double mat[3], int type)
{
	const double		tab[3 * NBR_MATERIAL] = {
		0.0215, 0.135, 0.05375, 0.25, 0.1745, 0.1, 0.329412, 0.2125, 0.25,
		0.19125, 0.24725, 0.19225,
		0.1745, 0.2225, 0.05, 0.20725, 0.01175, 0.18725, 0.223529,
		0.1275, 0.25, 0.0735, 0.1995, 0.19225,
		0.0215, 0.1575, 0.06625, 0.20725, 0.01175, 0.1745, 0.027451,
		0.054, 0.25, 0.19125, 0.0745, 0.19225};

	if (type < 0 || type >= NBR_MATERIAL)
		return (0);
	mat[0] = tab[type];
	mat[1] = tab[NBR_MATERIAL + type];
	mat[2] = tab[2 * NBR_MATERIAL + type];
	return (0);
}

int						rt_material_diffuse(double mat[3], int type)
{
	const double		tab[3 * NBR_MATERIAL] = {
		0.07568, 0.54, 0.18275, 1, 0.61424, 0.396, 0.780392, 0.714,
		0.4, 0.7038, 0.75164, 0.50754,
		0.61424, 0.89, 0.17, 0.829, 0.04136, 0.74151, 0.568627, 0.4284,
		0.4, 0.27048, 0.60648, 0.50754,
		0.07568, 0.63, 0.22525, 0.829, 0.04136, 0.69102, 0.113725, 0.18144,
		0.4, 0.0828, 0.22648, 0.50754};

	if (type < 0 || type >= NBR_MATERIAL)
		return (0);
	mat[0] = tab[type];
	mat[1] = tab[NBR_MATERIAL + type];
	mat[2] = tab[2 * NBR_MATERIAL + type];
	return (0);
}

int						rt_material_specular(double mat[3], int type)
{
	const double		tab[3 * NBR_MATERIAL] = {
		0.633, 0.316228, 0.332741, 0.296648, 0.727811, 0.297254, 0.992157,
		0.393548, 0.774597, 0.256777, 0.628281, 0.508274,
		0.727811, 0.316228, 0.328634, 0.296648, 0.626959, 0.30829, 0.941176,
		0.271906, 0.774597, 0.137622, 0.555802, 0.508274,
		0.633, 0.316228, 0.346435, 0.296648, 0.626959, 0.306678, 0.807843,
		0.166721, 0.774597, 0.086014, 0.366065, 0.508273};

	if (type < 0 || type >= NBR_MATERIAL)
		return (0);
	mat[0] = tab[type];
	mat[1] = tab[NBR_MATERIAL + type];
	mat[2] = tab[2 * NBR_MATERIAL + type];
	return (0);
}

double					rt_material_shininess(int type)
{
	const double		tab[NBR_MATERIAL] = {0.6, 0.1, 0.3, 0.088, 0.6, 0.1,
		0.21794872, 0.2, 0.6, 0.1, 0.4, 0.4};

	if (type < 0 || type >= NBR_MATERIAL)
		return (0);
	return (tab[type]);
}

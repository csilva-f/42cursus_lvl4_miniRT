/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ang_calculate.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csilva-f <csilva-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 22:29:47 by csilva-f          #+#    #+#             */
/*   Updated: 2023/10/23 23:14:27 by csilva-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

t_angles	three_d_angles(t_vector a, t_vector b)
{
	t_angles	ang;
	double		mags;
	t_vector	proj;

	mags = length(a) * length(b);
	ang.teta = acos(vector_dot(a, b) / mags);
	ang.fi = acos((a.vz * b.vz) / mags);
	proj = vector_sub(a, vector_mult_const(b, cos(ang.teta)));
	ang.psi = acos(proj.vx / sqrt(pow(proj.vx, 2) + pow(proj.vy, 2)));
	return (ang);
}

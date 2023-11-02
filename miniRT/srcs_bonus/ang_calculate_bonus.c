/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ang_calculate_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvieira <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 11:50:05 by fvieira           #+#    #+#             */
/*   Updated: 2023/11/02 11:50:08 by fvieira          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT_bonus.h"

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


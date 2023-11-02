/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coord_transform_2_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvieira <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 12:02:28 by fvieira           #+#    #+#             */
/*   Updated: 2023/11/02 12:02:31 by fvieira          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT_bonus.h"

t_vector	eq_transform(t_mini *m, double *angle)
{
	t_vector	final;
	t_vector	axis;

	final = (t_vector){0, 0, -1};
	*(angle) = acos(vector_dot(m->cam->vec, final) / length(m->cam->vec));
	*(angle) *= -1;
	axis = vector_cross(m->cam->vec, final);
	if (axis.vx == 0 && axis.vy == 0 && axis.vz == 0)
		axis.vy = 1;
	return (vector_norm(axis));
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coord_transform_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csilva-f <csilva-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 18:07:29 by csilva-f          #+#    #+#             */
/*   Updated: 2023/10/30 18:07:56 by csilva-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel_camera.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvieira <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 11:50:48 by fvieira           #+#    #+#             */
/*   Updated: 2023/08/29 21:18:18 by csilva-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

/*
https://www.scratchapixel.com/lessons/3d-basic-rendering/ray-tracing-generating
//-camera-rays/generating-camera-rays.html
*/

float	pixel_cam_x(float psx, t_mini *m)
{
	return ((2 * psx - 1) * m->g->width / \
			m->g->height * tan(m->cam->fov / 2.0));
}

float	pixel_cam_y(float psy, t_mini *m)
{
	return ((1 - 2 * psy) * tan(m->cam->fov / 2.0));
}

t_pos	pixel_pos(float psx, float psy, t_mini *m)
{
	t_pos	pos;

	pos.x = pixel_cam_x(psx, m);
	pos.y = pixel_cam_y(psy, m);
	pos.z = 0;
	return (pos);
}

t_vector	pixel_vec(t_pos pix)
{
	t_vector	vector;

	vector.vx = pix.x;
	vector.vy = pix.y;
	vector.vz = -1;
	return (vector_norm(vector));
}

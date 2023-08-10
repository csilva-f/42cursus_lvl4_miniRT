/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel_camera.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvieira <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 11:50:48 by fvieira           #+#    #+#             */
/*   Updated: 2023/08/04 11:50:50 by fvieira          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

/*
https://www.scratchapixel.com/lessons/3d-basic-rendering/ray-tracing-generating-camera-rays/generating-camera-rays.html
transformacao de pixel de ecra (raster) para pixel normalizado (ndc) para world space.
de raster para ndc esta a ser feito no lightrays.c:ray_create e em baixo, somar 0.5 
e dividir pelo comprimento total do eixo e mult por 2 e sub 1 para variar entre 
[-1,1], de ndc para world space sao as funcoes em baixo. x 'e  mult pelo
ratio de ecra e ambas as coordenadas pelo tan fov / 2
*/

float	pixel_cam_x(float psx, t_mini *m)
{
	return ((2 * psx - 1) * m->g->width / m->g->height * tan(m->cam->fov / 2));
}

float	pixel_cam_y(float psy, t_mini *m)
{
	return ((1 - 2 * psy) * tan(m->cam->fov / 2));
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
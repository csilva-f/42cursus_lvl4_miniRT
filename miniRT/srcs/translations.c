/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   translations.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csilva-f <csilva-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 11:50:23 by csilva-f          #+#    #+#             */
/*   Updated: 2023/09/23 12:54:17 by csilva-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

void	solid_iteration(t_mini *m, int x, int y, int z)
{
	while (m->sp)
	{
		m->sp->pos.x += x * -1;
		m->sp->pos.y += y * -1;
		m->sp->pos.z += z * -1;
		m->sp = m->sp->next;
	}
	while (m->cyl)
	{
		m->cyl->pos.x += x * -1;
		m->cyl->pos.y += y * -1;
		m->cyl->pos.z += z * -1;
		m->cyl = m->cyl->next;
	}
	while (m->plane)
	{
		m->plane->pos.x += x * -1;
		m->plane->pos.y += y * -1;
		m->plane->pos.z += z * -1;
		m->plane = m->plane->next;
	}
}

void	cam_translation(t_mini *m, int x, int y, int z)
{
	t_sphere	*t_sp;
	t_cylinder	*t_cyl;
	t_plane		*t_pl;

	t_sp = m->sp;
	t_cyl = m->cyl;
	t_pl = m->plane;
	solid_iteration(m, x, y, z);
	m->sp = t_sp;
	m->cyl = t_cyl;
	m->plane = t_pl;
	mlx_destroy_image(m->g->mlx, m->g->img);
	m->g->img = mlx_new_image(m->g->mlx, m->g->width, m->g->height);
	m->g->addr = mlx_get_data_addr(m->g->img, &m->g->bits_per_pixel, \
			&m->g->line_length, &m->g->endian);
	print_parser(m);
	raytracing(m);
}

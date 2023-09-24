/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_stuff.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvieira <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 18:33:31 by fvieira           #+#    #+#             */
/*   Updated: 2023/09/24 13:15:51 by csilva-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

int	my_mlx_pixel_put(t_mini *m, int x, int y, t_pos c)
{
	char	*dst;

	dst = m->g->addr + (y * m->g->line_length + x
			* (m->g->bits_per_pixel / 8));
	*(unsigned int *)dst = (0 << 24 | (int)c.x << 16 \
			| (int)c.y << 8 | (int)c.z);
	return (0);
}

int	close_game(t_mini *m)
{
	free_structs(m, 1);
	exit(EXIT_SUCCESS);
	return (EXIT_SUCCESS);
}

void	destroy_create_image(t_mini *m)
{
	mlx_destroy_image(m->g->mlx, m->g->img);
	m->g->img = mlx_new_image(m->g->mlx, m->g->width, m->g->height);
	m->g->addr = mlx_get_data_addr(m->g->img, &m->g->bits_per_pixel, \
			&m->g->line_length, &m->g->endian);
	raytracing(m);
}

void	raytracing(t_mini *m)
{
	static int	n = 0;

	ray_create(m);
	if (!n)
		fill_solid_list(m);
	n++;
}

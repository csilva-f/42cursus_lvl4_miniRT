/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_stuff.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvieira <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 18:33:31 by fvieira           #+#    #+#             */
/*   Updated: 2023/09/20 23:20:03 by csilva-f         ###   ########.fr       */
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

int	key_hook(int keycode, t_mini *m)
{
	if (keycode == ESC)
		close_game(m);
	if (keycode == S)
		reset_canvas(m, 1, 0);
	if (keycode == T1)
		reset_canvas(m, 0, 1);
	if (keycode == T2)
		reset_canvas(m, 0, -1);
	if (keycode == T3)
		cyl_height_diam(m, 1, 0, NULL);
	if (keycode == T4)
		cyl_height_diam(m, -1, 0, NULL);
	if (keycode == T5)
		cyl_height_diam(m, 0, 1, NULL);
	if (keycode == T6)
		cyl_height_diam(m, 0, -1, NULL);
	return (0);
}

void	raytracing(t_mini *m)
{
	ray_create(m);
}

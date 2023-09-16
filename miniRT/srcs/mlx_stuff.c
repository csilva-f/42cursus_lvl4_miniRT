/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_stuff.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvieira <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 18:33:31 by fvieira           #+#    #+#             */
/*   Updated: 2023/09/16 15:35:09 by csilva-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

int	my_mlx_pixel_put(t_mini *m, int x, int y, t_pos c)
{
	char	*dst;

	dst = m->g->addr + (y * m->g->line_length + x
			* (m->g->bits_per_pixel / 8));
	*(unsigned int *)dst = (0 << 24 | (int)c.x << 16 | (int)c.y << 8 | (int)c.z);
	//*(unsigned int *)dst = color;
	return (0);
}

int	close_game(t_mini *m)
{
	free_structs(m);
	exit(EXIT_SUCCESS);
	return (EXIT_SUCCESS);
}

int	key_hook(int keycode, t_mini *m)
{
	if (keycode == ESC)
		close_game(m);
	return (0);
}

void	raytracing(t_mini *m)
{
	ray_create(m);
}

	/*
	while etc
		my_pixel_put (color in pixel);
	*/

void	start_mlx(t_mini *m)
{
	m->g->mlx = mlx_init();
	m->g->width = 128 * 5;
	m->g->height = 72 * 5;
	m->g->win = mlx_new_window(m->g->mlx, m->g->width,
			m->g->height, "miniRT");
	m->g->img = mlx_new_image(m->g->mlx, m->g->width, m->g->height);
	m->g->addr = mlx_get_data_addr(m->g->img, &m->g->bits_per_pixel,
			&m->g->line_length, &m->g->endian);
	raytracing(m);
	mlx_key_hook(m->g->win, key_hook, &m);
	mlx_hook(m->g->win, 17, 1L << 17, close_game, &m);
	//mlx_loop(m->g->mlx);
}

	//mlx_mouse_hook(m->g->win, mouse_hook, &m);

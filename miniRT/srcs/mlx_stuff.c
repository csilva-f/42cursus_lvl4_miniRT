/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_stuff.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvieira <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 18:33:31 by fvieira           #+#    #+#             */
/*   Updated: 2023/09/19 23:41:29 by csilva-f         ###   ########.fr       */
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
	free_structs(m);
	exit(EXIT_SUCCESS);
	return (EXIT_SUCCESS);
}

void	reset_canvas(t_mini *m, int r, int inc)
{
	close(m->fd);
	get_values(m);
	if (!r)
	{
		if (inc)
		{
			printf("d esfera: %f\n", m->sp->d);
			m->sp->d += m->sp->d * 0.1;
			printf("aqui\n");
		}
		else
			m->sp->d -= m->sp->d * 0.1;
	}
	else
	mlx_destroy_image(m->g->mlx, m->g->img);
	m->g->img = mlx_new_image(m->g->mlx, m->g->width, m->g->height);
	m->g->addr = mlx_get_data_addr(m->g->img, &m->g->bits_per_pixel, \
			&m->g->line_length, &m->g->endian);
	print_parser(m);
	raytracing(m);
}

int	key_hook(int keycode, t_mini *m)
{
	printf("keycode: %i\n", keycode);
	if (keycode == ESC)
		close_game(m);
	if (keycode == S)
		reset_canvas(m, 1, 0);
	if (keycode == T1)
		reset_canvas(m, 0, 1);
	if (keycode == T2)
		reset_canvas(m, 0, 0);
	return (0);
}

void	raytracing(t_mini *m)
{
	ray_create(m);
}

/*void	start_mlx(t_mini *m)
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
}*/

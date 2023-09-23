/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_stuff.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvieira <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 18:33:31 by fvieira           #+#    #+#             */
/*   Updated: 2023/09/23 19:03:08 by csilva-f         ###   ########.fr       */
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

void	key_hook_aux(int keycode, t_mini *m)
{
	if (keycode == DOWN && !m->hl)
		cam_translation(m, 0, -1, 0);
	else if (keycode == F && !m->hl)
		cam_translation(m, 0, 0, 1);
	else if (keycode == B && !m->hl)
		cam_translation(m, 0, 0, -1);
	else if (keycode == T)
	{
		m->action = 't';
		rotate_translate(m, 1, 0, '0');	
	}
	else if (keycode == R)
	{
		m->action = 'r';
		rotate_translate(m, 2, 0, '0');
	}
	else if (keycode == RIGHT && m->hl)
		rotate_translate(m, 0, 0, 'r');
	else if (keycode == LEFT && m->hl)
		rotate_translate(m, 0, 0, 'l');
	else if (keycode == UP && m->hl)
		rotate_translate(m, 0, 0, 'u');
	else if (keycode == DOWN && m->hl)
		rotate_translate(m, 0, 0, 'd');
	else if (keycode == F && m->hl)
		rotate_translate(m, 0, 0, 'f');
	else if (keycode == B && m->hl)
		rotate_translate(m, 0, 0, 'b');
	else if (keycode == I)
		rotate_translate(m, 0, 1, '0');
}

int	key_hook(int keycode, t_mini *m)
{
	printf("keycode: %d\n", keycode);
	if (keycode == ESC)
		close_game(m);
	else if (keycode == S)
		reset_canvas(m, 1, 0);
	else if (keycode == T1)
		reset_canvas(m, 0, 1);
	else if (keycode == T2)
		reset_canvas(m, 0, -1);
	else if (keycode == T3)
		cyl_height_diam(m, 1, 0, NULL);
	else if (keycode == T4)
		cyl_height_diam(m, -1, 0, NULL);
	else if (keycode == T5)
		cyl_height_diam(m, 0, 1, NULL);
	else if (keycode == T6)
		cyl_height_diam(m, 0, -1, NULL);
	else if (keycode == RIGHT && !m->hl)
		cam_translation(m, 1, 0, 0);
	else if (keycode == LEFT && !m->hl)
		cam_translation(m, -1, 0, 0);
	else if (keycode == UP && !m->hl)
		cam_translation(m, 0, 1, 0);
	else
		key_hook_aux(keycode, m);
	return (0);
}

void	raytracing(t_mini *m)
{
	static int	n = 0;
	ray_create(m);
	if (!n)
		fill_solid_list(m);
	n++;
}

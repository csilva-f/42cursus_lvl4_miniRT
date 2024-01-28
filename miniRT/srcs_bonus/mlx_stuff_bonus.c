/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_stuff_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvieira <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 18:33:31 by fvieira           #+#    #+#             */
/*   Updated: 2023/11/26 17:48:35 by csilva-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT_bonus.h"

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

void	print_action(t_mini *m, int action)
{
	if (action)
	{
		mlx_set_font(m->g->mlx, m->g->win, "6x12");
		if (action == 1)
			mlx_string_put(m->g->mlx, m->g->win, 10, 15, \
					WHITE, "SOLIDS TRANSLATION");
		else if (action == 2)
			mlx_string_put(m->g->mlx, m->g->win, 10, 15, \
					WHITE, "SOLIDS ROTATION");
		else if (action == 3)
			mlx_string_put(m->g->mlx, m->g->win, 10, 15, \
					WHITE, "SOLIDS DIMENSIONS");
		else if (action == 4)
			mlx_string_put(m->g->mlx, m->g->win, 10, 15, \
					WHITE, "CYLINDER HEIGHT");
		else if (action == 5)
			mlx_string_put(m->g->mlx, m->g->win, 10, 15, \
					WHITE, "LIGHT TRANSLATION");
	}
}

void	destroy_create_image(t_mini *m, int action)
{
	mlx_destroy_image(m->g->mlx, m->g->img);
	m->g->img = mlx_new_image(m->g->mlx, m->g->width, m->g->height);
	m->g->addr = mlx_get_data_addr(m->g->img, &m->g->bits_per_pixel, \
			&m->g->line_length, &m->g->endian);
	raytracing(m);
	print_action(m, action);
}

void	raytracing(t_mini *m)
{
	static int	n = 0;

	ray_create(m);
	if (!n || m->reset)
	{
		fill_solid_list(m);
		fill_light_list(m);
	}
	n++;
}

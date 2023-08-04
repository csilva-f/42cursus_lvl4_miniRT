/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_stuff.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvieira <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 18:33:31 by fvieira           #+#    #+#             */
/*   Updated: 2023/08/03 18:33:33 by fvieira          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

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

void	raytracing(t_mini *m) //😎
{
	ray_create(m);
	/*
	while etc
		my_pixel_put (color in pixel);
	*/
}

void	start_mlx(t_mini *m)
{
	m->g->mlx = mlx_init();
	m->g->width = 1280;
	m->g->height = 720;
	m->g->win = mlx_new_window(m->g->mlx, m->g->width,
			m->g->height, "miniRT");
	m->g->img = mlx_new_image(m->g->mlx, m->g->width, m->g->height);
	raytracing(m);
	mlx_key_hook(m->g->win, key_hook, &m);
	//mlx_mouse_hook(m->g->win, mouse_hook, &m);
	mlx_hook(m->g->win, 17, 1L << 17, close_game, &m);
	mlx_loop(m->g->mlx);
}
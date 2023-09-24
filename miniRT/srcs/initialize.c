/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csilva-f <csilva-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 19:37:13 by csilva-f          #+#    #+#             */
/*   Updated: 2023/09/24 17:02:40 by csilva-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

void	init(t_mini *mini)
{
	mini->is_valid = 1;
	mini->hl = 0;
	mini->action = '0';
	mini->reset = 0;
	mini->grey_c = (t_pos){255, 0, 0};
	mini->counter_a = 0;
	mini->counter_c = 0;
	mini->counter_l = 0;
	mini->al = malloc(sizeof(t_al));
	mini->cam = malloc(sizeof(t_cam));
	mini->light = malloc(sizeof(t_light));
	if (!mini->al || !mini->cam || !mini->light)
		return ;
	mini->plane = NULL;
	mini->sp = NULL;
	mini->cyl = NULL;
	mini->ray = NULL;
	mini->s = NULL;
}

void	init_canvas(t_mini *m)
{
	m->g = malloc(sizeof(t_graphics));
	if (!m->g)
		return ;
	m->g->mlx = mlx_init();
	m->g->menu_mlx = mlx_init();
	m->g->width = WIDTH * 10;
	m->g->height = HEIGHT * 10;
	m->g->win = mlx_new_window(m->g->mlx, m->g->width, \
			m->g->height, "miniRT");
	m->g->menu_win = mlx_new_window(m->g->menu_mlx, 300, 500, "Menu");
	m->g->img = mlx_new_image(m->g->mlx, m->g->width, m->g->height);
	m->g->menu_img = mlx_new_image(m->g->menu_mlx, 300, 500);
	m->g->addr = mlx_get_data_addr(m->g->img, &m->g->bits_per_pixel, \
			&m->g->line_length, &m->g->endian);
	create_menu(m);
	raytracing(m);
	mlx_key_hook(m->g->win, key_hook, m);
	mlx_hook(m->g->win, 17, 1L << 17, close_game, m);
	mlx_loop(m->g->mlx);
}

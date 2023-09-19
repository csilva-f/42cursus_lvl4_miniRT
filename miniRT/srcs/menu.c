/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csilva-f <csilva-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 16:41:44 by csilva-f          #+#    #+#             */
/*   Updated: 2023/09/19 19:57:01 by csilva-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

void	create_menu(t_mini *m)
{
	void	*mlx;
	void	*win;
	int		y;

	y = 0;
	mlx = m->g->menu_mlx;
	win = m->g->menu_win;
	mlx_set_font(mlx, win, "6x14");
	mlx_string_put(mlx, win, 10, y += 15, BLUE, "SOLIDS DIMENSIONS");
	mlx_set_font(mlx, win, "6x12");
	mlx_string_put(mlx, win, 10, y += 15, WHITE, "Sphere diameter: 1(+) 2(-)");
	mlx_string_put(mlx, win, 10, y += 20, WHITE, "Rotate:");
	mlx_string_put(mlx, win, 10, y += 15, WHITE, "X-Axis");
	mlx_string_put(mlx, win, 10, y += 15, WHITE, "Y-Axis");
	mlx_string_put(mlx, win, 10, y += 15, WHITE, "Z-Axis");
	mlx_string_put(mlx, win, 10, y += 20, WHITE, "Reset: [S]");
	mlx_string_put(mlx, win, 10, y += 20, WHITE, "Exit: ESC");
}

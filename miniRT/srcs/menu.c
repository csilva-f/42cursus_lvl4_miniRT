/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csilva-f <csilva-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 16:41:44 by csilva-f          #+#    #+#             */
/*   Updated: 2023/09/23 17:40:17 by csilva-f         ###   ########.fr       */
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
	mlx_set_font(mlx, win, "6x12");
	mlx_string_put(mlx, win, 10, y += 15, BLUE, "SOLIDS DIMENSIONS");
	mlx_string_put(mlx, win, 10, y += 70, BLUE, "CAMERA TRANSLATION");
	mlx_string_put(mlx, win, 10, y -= 55, \
			WHITE, "Sphere diameter:   [1]+ [2]-");
	mlx_string_put(mlx, win, 10, y += 15, \
			WHITE, "Cylinder diameter: [3]+ [4]-");
	mlx_string_put(mlx, win, 10, y += 15, \
			WHITE, "Cylinder height:   [5]+ [6]-");
	mlx_string_put(mlx, win, 10, y += 40, WHITE, "X-Axis: [RIGHT] [LEFT]");
	mlx_string_put(mlx, win, 10, y += 15, WHITE, "Y-Axis: [UP]    [DOWN]");
	mlx_string_put(mlx, win, 10, y += 15, WHITE, "Z-Axis: [F] [B]");
	mlx_string_put(mlx, win, 10, y += 20, WHITE, "Reset: [S]");
	mlx_string_put(mlx, win, 10, y += 20, WHITE, "Exit: ESC");
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csilva-f <csilva-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 16:41:44 by csilva-f          #+#    #+#             */
/*   Updated: 2023/12/04 20:55:34 by csilva-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

void	create_menu_aux(int y, void *mlx, void *win)
{
	mlx_string_put(mlx, win, 10, y += 40, WHITE, "Cylinder height:   + -");
	mlx_string_put(mlx, win, 10, y += 40, WHITE, "X-Axis:           arrows");
	mlx_string_put(mlx, win, 10, y += 15, WHITE, "Y-Axis:           arrows");
	mlx_string_put(mlx, win, 10, y += 15, WHITE, "Z-Axis:          [F]  [B]");
	mlx_string_put(mlx, win, 10, y += 110, WHITE, "X-Axis:           arrows");
	mlx_string_put(mlx, win, 10, y += 15, WHITE, "Y-Axis:           arrows");
	mlx_string_put(mlx, win, 10, y += 15, WHITE, "Z-Axis:          [F]  [B]");
	mlx_string_put(mlx, win, 10, y += 25, BLUE, "CAMERA ROTATION");
	mlx_string_put(mlx, win, 10, y += 15, WHITE, "X-Axis:            [X]");
	mlx_string_put(mlx, win, 10, y += 15, WHITE, "Y-Axis:            [Y]");
	mlx_string_put(mlx, win, 10, y += 15, WHITE, "Z-Axis:            [Z]");
	mlx_string_put(mlx, win, 10, y += 25, BLUE, "LIGHT TRANSLATION MODE [L]");
	mlx_string_put(mlx, win, 10, y += 15, WHITE, "X-Axis:           arrows");
	mlx_string_put(mlx, win, 10, y += 15, WHITE, "Y-Axis:           arrows");
	mlx_string_put(mlx, win, 10, y += 15, WHITE, "Z-Axis:          [F]  [B]");
	mlx_string_put(mlx, win, 10, y += 30, BLUE, "RESET: [S]");
	mlx_string_put(mlx, win, 10, y += 20, BLUE, "EXIT: [ESC]");
}

void	create_menu(t_mini *m)
{
	void	*mlx;
	void	*win;
	int		y;

	y = 0;
	mlx = m->g->menu_mlx;
	win = m->g->menu_win;
	mlx_set_font(mlx, win, "6x12");
	mlx_string_put(mlx, win, 10, y += 15, WHITE, \
			"Some instructions need mode activation");
	mlx_string_put(mlx, win, 10, y += 15, WHITE, \
			"After activating a mode, you can iterate");
	mlx_string_put(mlx, win, 10, y += 15, WHITE, \
			"through all available solids using [I]");
	mlx_string_put(mlx, win, 10, y += 20, BLUE, "SOLIDS DIMENSIONS MODE [D]");
	mlx_string_put(mlx, win, 10, y += 55, BLUE, "CYLINDER HEIGHT MODE [H]");
	mlx_string_put(mlx, win, 10, y += 40, BLUE, "SOLIDS TRANSLATION MODE [T]");
	mlx_string_put(mlx, win, 10, y += 70, BLUE, "SOLIDS ROTATION MODE [R]");
	mlx_string_put(mlx, win, 10, y += 15, WHITE, "X-Axis:            [X]");
	mlx_string_put(mlx, win, 10, y += 15, WHITE, "Y-Axis:            [Y]");
	mlx_string_put(mlx, win, 10, y += 15, WHITE, "Z-Axis:            [Z]");
	mlx_string_put(mlx, win, 10, y += 25, BLUE, "CAMERA TRANSLATION");
	mlx_string_put(mlx, win, 10, y -= 220, WHITE, "Sphere diameter:   + -");
	mlx_string_put(mlx, win, 10, y += 15, WHITE, "Cylinder diameter: + -");
	create_menu_aux(y, mlx, win);
}

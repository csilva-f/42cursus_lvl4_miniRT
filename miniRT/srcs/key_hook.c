/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csilva-f <csilva-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 13:02:16 by csilva-f          #+#    #+#             */
/*   Updated: 2023/09/24 13:13:12 by csilva-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

void	key_hook_aux_2(int keycode, t_mini *m)
{
	if (keycode == DOWN && m->hl)
		rotate_translate(m, 0, 0, 'd');
	else if (keycode == F && m->hl)
		rotate_translate(m, 0, 0, 'f');
	else if (keycode == B && m->hl)
		rotate_translate(m, 0, 0, 'b');
	else if (keycode == I)
		rotate_translate(m, 0, 1, '0');
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
	else
		key_hook_aux_2(keycode, m);
}

int	key_hook(int keycode, t_mini *m)
{
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

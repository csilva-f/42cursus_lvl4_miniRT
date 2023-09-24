/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csilva-f <csilva-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 13:02:16 by csilva-f          #+#    #+#             */
/*   Updated: 2023/09/24 17:30:43 by csilva-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

void	key_hook_aux_2(int keycode, t_mini *m)
{
	if (keycode == UP && m->hl)
		dim_rot_trans(m, 0, 0, 'u');
	else if (keycode == DOWN && m->hl)
		dim_rot_trans(m, 0, 0, 'd');
	else if (keycode == F && m->hl)
		dim_rot_trans(m, 0, 0, 'f');
	else if (keycode == B && m->hl)
		dim_rot_trans(m, 0, 0, 'b');
	else if (keycode == I)
		dim_rot_trans(m, 0, 1, '0');
}

void	key_hook_aux(int keycode, t_mini *m)
{
	if (keycode == R)
	{
		m->action = 'r';
		dim_rot_trans(m, 2, 0, '0');
	}
	else if (keycode == D)
	{
		m->action = 'd';
		dim_rot_trans(m, 3, 0, '0');
	}
	else if (keycode == H)
	{
		m->action = 'h';
		dim_rot_trans(m, 4, 0, '0');
	}
	else if (keycode == PLUS && m->hl)
		dim_rot_trans(m, 0, 0, 'i');
	else if (keycode == MINUS && m->hl)
		dim_rot_trans(m, 0, 0, 'd');
	else if (keycode == RIGHT && m->hl)
		dim_rot_trans(m, 0, 0, 'r');
	else if (keycode == LEFT && m->hl)
		dim_rot_trans(m, 0, 0, 'l');
	else
		key_hook_aux_2(keycode, m);
}

int	key_hook(int keycode, t_mini *m)
{
	printf("keycode: %i\nhl: %i\n", keycode, m->hl);
	if (keycode == ESC)
		close_game(m);
	else if (keycode == S)
		reset_canvas(m);
	else if (keycode == RIGHT && !m->hl)
		cam_translation(m, 1, 0, 0);
	else if (keycode == LEFT && !m->hl)
		cam_translation(m, -1, 0, 0);
	else if (keycode == UP && !m->hl)
		cam_translation(m, 0, 1, 0);
	else if (keycode == DOWN && !m->hl)
		cam_translation(m, 0, -1, 0);
	else if (keycode == F && !m->hl)
		cam_translation(m, 0, 0, 1);
	else if (keycode == B && !m->hl)
		cam_translation(m, 0, 0, -1);
	else if (keycode == T)
	{
		m->action = 't';
		dim_rot_trans(m, 1, 0, '0');
	}
	else
		key_hook_aux(keycode, m);
	return (0);
}

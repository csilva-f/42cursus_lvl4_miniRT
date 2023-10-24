/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csilva-f <csilva-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 13:02:16 by csilva-f          #+#    #+#             */
/*   Updated: 2023/10/24 22:26:25 by csilva-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

void	key_hook_aux_3(int keycode, t_mini *m)
{
	if (keycode == B && m->action == 'l')
		light_translation(m, 0, 0, -1);
	else if (keycode == X && m->action == 'r')
		dim_rot_trans(m, 0, 0, 'x');
	else if (keycode == Y && m->action == 'r')
		dim_rot_trans(m, 0, 0, 'y');
	else if (keycode == Z && m->action == 'r')
		dim_rot_trans(m, 0, 0, 'z');
	else if (keycode == X && !m->hl)
		cam_rotation(m, 'x', (double [2]){0}, NULL);
	else if (keycode == Y && !m->hl)
		cam_rotation(m, 'y', (double [2]){0}, NULL);
	else if (keycode == Z && !m->hl)
		cam_rotation(m, 'z', (double [2]){0}, NULL);
}

void	key_hook_aux_2(int keycode, t_mini *m)
{
	if (keycode == L)
	{
		if (m->action == 'l')
		{
			m->action = '0';
			destroy_create_image(m, 0);
		}
		else if (m->action == '0')
		{
			m->action = 'l';
			print_action(m, 5);
		}
	}
	else if (keycode == RIGHT && m->action == 'l')
		light_translation(m, 1, 0, 0);
	else if (keycode == LEFT && m->action == 'l')
		light_translation(m, -1, 0, 0);
	else if (keycode == UP && m->action == 'l')
		light_translation(m, 0, 1, 0);
	else if (keycode == DOWN && m->action == 'l')
		light_translation(m, 0, -1, 0);
	else if (keycode == F && m->action == 'l')
		light_translation(m, 0, 0, 1);
	else
		key_hook_aux_3(keycode, m);
}

void	key_hook_dim_rot_tr(int k, t_mini *m)
{
	if (m->action == 'd' || m->action == 'h')
	{
		if (k == PLUS)
			dim_rot_trans(m, 0, 0, 'i');
		else if (k == MINUS)
			dim_rot_trans(m, 0, 0, 'd');
	}
	else if (m->action == 't')
	{
		if (k == RIGHT)
			dim_rot_trans(m, 0, 0, 'r');
		else if (k == LEFT)
			dim_rot_trans(m, 0, 0, 'l');
		else if (k == UP)
			dim_rot_trans(m, 0, 0, 'u');
		else if (k == DOWN)
			dim_rot_trans(m, 0, 0, 'd');
		else if (k == F)
			dim_rot_trans(m, 0, 0, 'f');
		else if (k == B)
			dim_rot_trans(m, 0, 0, 'b');
	}
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
	else if (keycode != I && m->hl && (m->action == 't' || \
				m->action == 'd' || m->action == 'h'))
		key_hook_dim_rot_tr(keycode, m);
	else if (keycode == I)
		dim_rot_trans(m, 0, 1, '0');
	else
		key_hook_aux_2(keycode, m);
}

int	key_hook(int keycode, t_mini *m)
{
	if (keycode == ESC)
		close_game(m);
	else if (keycode == S)
		reset_canvas(m);
	else if (keycode == RIGHT && !m->hl && m->action == '0')
		cam_translation(m, 1, 0, 0);
	else if (keycode == LEFT && !m->hl && m->action == '0')
		cam_translation(m, -1, 0, 0);
	else if (keycode == UP && !m->hl && m->action == '0')
		cam_translation(m, 0, 1, 0);
	else if (keycode == DOWN && !m->hl && m->action == '0')
		cam_translation(m, 0, -1, 0);
	else if (keycode == F && !m->hl && m->action == '0')
		cam_translation(m, 0, 0, 1);
	else if (keycode == B && !m->hl && m->action == '0')
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

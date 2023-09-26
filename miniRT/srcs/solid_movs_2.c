/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solid_movs_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csilva-f <csilva-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 17:34:55 by csilva-f          #+#    #+#             */
/*   Updated: 2023/09/24 17:48:49 by csilva-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

void	highlight_solid(t_mini *m)
{
	if (m->s->l == 'P')
	{
		m->s->old_color = m->s->pl->color;
		m->s->pl->color = m->grey_c;
	}
	else if (m->s->l == 'S')
	{
		m->s->old_color = m->s->sp->color;
		m->s->sp->color = m->grey_c;
	}
	else if (m->s->l == 'C')
	{
		m->s->old_color = m->s->cyl->color;
		m->s->cyl->color = m->grey_c;
	}
}

void	apply_action_iterate(t_mini *m, int iter)
{
	if (m->s->l == 'P')
		m->s->pl->color = m->s->old_color;
	else if (m->s->l == 'S')
		m->s->sp->color = m->s->old_color;
	else if (m->s->l == 'C')
		m->s->cyl->color = m->s->old_color;
	if (iter && m->hl)
	{
		m->s = m->s->next;
		while (m->action == 'd' && m->s->l != 'S' && m->s->l != 'C')
			m->s = m->s->next;
		while (m->action == 'h' && m->s->l != 'C')
			m->s = m->s->next;
		highlight_solid(m);
	}
	else
	{
		m->action = '0';
		m->hl = 0;
	}
}

void	init_hl_mode(t_mini *m, int action)
{
	m->hl = 1;
	while (m->s->head != 1)
		m->s = m->s->next;
	if (action == 1)
		m->action = 't';
	else if (action == 2)
		m->action = 'r';
	else if (action == 3)
		m->action = 'd';
	else if (action == 4)
		m->action = 'h';
	while (action == 3 && m->s->l != 'S' && m->s->l != 'C')
		m->s = m->s->next;
	while (action == 4 && m->s->l != 'C')
		m->s = m->s->next;
	highlight_solid(m);
}

int	def_tip_action(t_mini *m, int action)
{
	if (m->action == 't')
		action = 1;
	else if (m->action == 'r')
		action = 2;
	else if (m->action == 'd')
		action = 3;
	else if (m->action == 'h')
		action = 4;
	else
		action = 0;
	return (action);
}

void	dim_rot_trans(t_mini *m, int action, int iter, char c)
{
	if (!m->hl && action)
		init_hl_mode(m, action);
	else
	{
		if ((action || iter) && m->hl)
			apply_action_iterate(m, iter);
		else
		{
			if (m->action == 'd' || m->action == 'h')
				solids_dimensions(m, c);
			else if (m->action == 't')
				translate_solids(m, c);
			else if (m->action == 'r')
				rotate_solids(m, c);
		}
	}
	destroy_create_image(m, def_tip_action(m, action));
}

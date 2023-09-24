/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solid_movs_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csilva-f <csilva-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 17:34:55 by csilva-f          #+#    #+#             */
/*   Updated: 2023/09/24 13:13:46 by csilva-f         ###   ########.fr       */
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
	if (iter)
	{
		m->s = m->s->next;
		highlight_solid(m);
	}
	else
	{
		m->action = '0';
		m->hl = 0;
	}
}

void	rotate_translate(t_mini *m, int action, int iter, char c)
{
	if (!m->hl)
	{
		m->hl = 1;
		while (m->s->head != 1)
			m->s = m->s->next;
		highlight_solid(m);
		if (action == 1)
			m->action = 't';
		else if (action == 2)
			m->action = 'r';
	}
	else
	{
		if (action || iter)
			apply_action_iterate(m, iter);
		else
		{
			if (m->action == 't')
				translate_solids(m, c);
		}
	}
	destroy_create_image(m);
}

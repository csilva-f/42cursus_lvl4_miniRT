/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   translations_2_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csilva-f <csilva-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 23:13:46 by csilva-f          #+#    #+#             */
/*   Updated: 2023/11/26 17:49:45 by csilva-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT_bonus.h"

void	light_translation(t_mini *m, int x, int y, int z)
{
	m->llst->l->pos.x += x * 1;
	m->llst->l->pos.y += y * 1;
	m->llst->l->pos.z += z * 1;
	destroy_create_image(m, 5);
}

void	init_hl_light_mode(t_mini *m)
{
	m->hl = 1;
	while (m->llst->head != 1)
		m->llst = m->llst->next;
	m->action = 'l';
	m->llst->old_color = m->llst->l->color;
	destroy_create_image(m, 5);
}

void	iterate_lights(t_mini *m, int iter)
{
	m->llst->l->color = m->llst->old_color;
	if (iter && m->hl && m->llst->next)
	{
		m->llst = m->llst->next;
		m->llst->old_color = m->llst->l->color;
		destroy_create_image(m, 5);
	}
	else
	{
		m->action = '0';
		m->hl = 0;
		destroy_create_image(m, 0);
	}
}

void	light_movs(t_mini *m, int action, char c, int iter)
{
	if (!m->hl && action)
		init_hl_light_mode(m);
	else
	{
		if (m->hl && (iter || action))
			iterate_lights(m, iter);
		else if (m->action == 'l')
		{
			if (c == 'r')
				light_translation(m, 1, 0, 0);
			else if (c == 'l')
				light_translation(m, -1, 0, 0);
			else if (c == 'u')
				light_translation(m, 0, 1, 0);
			else if (c == 'd')
				light_translation(m, 0, -1, 0);
			else if (c == 'f')
				light_translation(m, 0, 0, 1);
			else if (c == 'b')
				light_translation(m, 0, 0, -1);
			destroy_create_image(m, 5);
		}
	}
}

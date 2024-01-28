/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alter_solid_dim_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csilva-f <csilva-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 23:17:29 by csilva-f          #+#    #+#             */
/*   Updated: 2023/11/07 22:58:40 by csilva-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT_bonus.h"

void	reset_canvas(t_mini *m)
{
	free_structs(m, 0);
	init(m);
	m->reset = 1;
	get_values(m);
	m->init = 0;
	destroy_create_image(m, 0);
	m->reset = 0;
}

void	solids_dimensions(t_mini *m, char c, int n)
{
	if (c == 'd')
		n = -1;
	if (m->action == 'd')
	{
		if (m->s->l == 'S')
		{
			m->s->sp->d = m->s->sp->d + n * m->s->sp->d * 0.1;
			m->s->sp->d_squared = m->s->sp->d * m->s->sp->d;
		}
		else if (m->s->l == 'C')
		{
			m->s->cyl->d = m->s->cyl->d + n * 0.1 * m->s->cyl->d;
			m->s->cyl->d_squared = m->s->cyl->d * m->s->cyl->d;
		}
		else if (m->s->l == 'O')
		{
			m->s->co->ang = m->s->co->ang + n * 0.1 * m->s->co->ang;
			m->s->co->k = tan(m->s->co->ang);
			m->s->co->k_k = 1 + pow(m->s->co->k, 2);
		}
	}
	else if (m->action == 'h' && m->s->l == 'C')
		m->s->cyl->h = m->s->cyl->h + n * 0.1 * m->s->cyl->h;
	else if (m->action == 'h' && m->s->l == 'O')
		m->s->co->h = m->s->co->h + n * 0.1 * m->s->co->h;
}

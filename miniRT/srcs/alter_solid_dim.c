/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alter_solid_dim.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csilva-f <csilva-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 23:17:29 by csilva-f          #+#    #+#             */
/*   Updated: 2023/10/24 00:27:24 by csilva-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

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

void	solids_dimensions(t_mini *m, char c)
{
	int	n;

	n = 1;
	if (c == 'd')
		n = -1;
	// vais ver isto quando fizeres a norma, tive de adicionar este if
	// pq a esfera e o cilindro aumentam com a tecla F e B em vez de ser so
	// com o + e -, mas o problema deve estar para tras
	if (c == 'f' || c == 'b')
		return ;
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
	}
	else if (m->action == 'h' && m->s->l == 'C')
		m->s->cyl->h = m->s->cyl->h + n * 0.1 * m->s->cyl->h;
}

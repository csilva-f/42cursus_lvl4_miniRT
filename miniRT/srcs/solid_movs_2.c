/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solid_movs_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csilva-f <csilva-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 17:34:55 by csilva-f          #+#    #+#             */
/*   Updated: 2023/09/23 19:05:36 by csilva-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

void	highlight_solid(t_mini *m)
{
	printf("solid: %c\n", m->s->l);
	if (m->s->l == 'P')
	{
		m->s->old_color = m->s->pl->color;
		m->s->pl->color = m->grey_c;
	}
	else if (m->s->l == 'S')
	{
		printf("aqui6\n");
		m->s->old_color = m->s->sp->color;
		m->s->sp->color = m->grey_c;
	}
	else if (m->s->l == 'C')
	{
		m->s->old_color = m->s->cyl->color;
		m->s->cyl->color = m->grey_c;
	}
}

void	rotate_translate(t_mini *m, int action, int	iter, char c)
{
	if (!m->hl)
	{
		printf("aqui2\n");
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
		printf("aqui1\n");
		if (action || iter)
		{
			if (m->s->l == 'P')
			{
				printf("aqui5\n");
				m->s->pl->color = m->s->old_color;
			}
			else if (m->s->l == 'S')
				m->s->sp->color = m->s->old_color;
			else if (m->s->l == 'S')
				m->s->cyl->color = m->s->old_color;
			if (iter)
			{
				printf("aqui3\n");
				m->s = m->s->next;
				highlight_solid(m);
			}
			else
			{
				printf("aqui4\n");
				m->action = '0';
			}
		}
		else
		{
			if (m->action == 't')
			{
				if (c == 'r')
				{
					if (m->s->l == 'P')
						m->s->pl->pos.x += 1;
					else if (m->s->l == 'S')
						m->s->sp->pos.x += 1;
					else if (m->s->l == 'S')
						m->s->cyl->pos.x += 1;
				}
				else if (c == 'l')
				{
					if (m->s->l == 'P')
						m->s->pl->pos.x -= 1;
					else if (m->s->l == 'S')
						m->s->sp->pos.x -= 1;
					else if (m->s->l == 'S')
						m->s->cyl->pos.x -= 1;
				}
				if (c == 'u')
				{
					if (m->s->l == 'P')
						m->s->pl->pos.y += 1;
					else if (m->s->l == 'S')
						m->s->sp->pos.y += 1;
					else if (m->s->l == 'S')
						m->s->cyl->pos.y += 1;
				}
				else if (c == 'd')
				{
					if (m->s->l == 'P')
						m->s->pl->pos.y -= 1;
					else if (m->s->l == 'S')
						m->s->sp->pos.y -= 1;
					else if (m->s->l == 'S')
						m->s->cyl->pos.y -= 1;
				}
				if (c == 'f')
				{
					if (m->s->l == 'P')
						m->s->pl->pos.z += 1;
					else if (m->s->l == 'S')
						m->s->sp->pos.z += 1;
					else if (m->s->l == 'S')
						m->s->cyl->pos.z += 1;
				}
				else if (c == 'b')
				{
					if (m->s->l == 'P')
						m->s->pl->pos.z -= 1;
					else if (m->s->l == 'S')
						m->s->sp->pos.z -= 1;
					else if (m->s->l == 'S')
						m->s->cyl->pos.z -= 1;
				}
			}
		}
	}
	printf("aqui7\n");
	mlx_destroy_image(m->g->mlx, m->g->img);
	printf("aqui8\n");
	m->g->img = mlx_new_image(m->g->mlx, m->g->width, m->g->height);
	m->g->addr = mlx_get_data_addr(m->g->img, &m->g->bits_per_pixel, \
			&m->g->line_length, &m->g->endian);
	printf("aqui9\n");
	raytracing(m);
	printf("aqui10\n");
}

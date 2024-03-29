/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   translations_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csilva-f <csilva-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 11:50:23 by csilva-f          #+#    #+#             */
/*   Updated: 2023/11/07 23:16:40 by csilva-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT_bonus.h"

void	solid_iteration_aux(t_mini *m, int x, int y, int z)
{
	while (m->co)
	{
		m->co->pos.x += x * -1;
		m->co->pos.y += y * -1;
		m->co->pos.z += z * -1;
		m->co = m->co->next;
	}
}

void	solid_iteration(t_mini *m, int x, int y, int z)
{
	while (m->sp)
	{
		m->sp->pos.x += x * -1;
		m->sp->pos.y += y * -1;
		m->sp->pos.z += z * -1;
		m->sp = m->sp->next;
	}
	while (m->cyl)
	{
		m->cyl->pos.x += x * -1;
		m->cyl->pos.y += y * -1;
		m->cyl->pos.z += z * -1;
		m->cyl = m->cyl->next;
	}
	while (m->plane)
	{
		m->plane->pos.x += x * -1;
		m->plane->pos.y += y * -1;
		m->plane->pos.z += z * -1;
		m->plane = m->plane->next;
	}
	solid_iteration_aux(m, x, y, z);
}

void	cam_translation(t_mini *m, int x, int y, int z)
{
	t_sphere	*t_sp;
	t_cylinder	*t_cyl;
	t_plane		*t_pl;
	t_cone		*t_co;
	t_light		*t_l;

	t_sp = m->sp;
	t_cyl = m->cyl;
	t_co = m->co;
	t_pl = m->plane;
	t_l = m->light;
	solid_iteration(m, x, y, z);
	while (m->light)
	{
		m->light->pos.x += x * -1;
		m->light->pos.y += y * -1;
		m->light->pos.z += z * -1;
		m->light = m->light->next;
	}
	m->sp = t_sp;
	m->cyl = t_cyl;
	m->co = t_co;
	m->plane = t_pl;
	m->light = t_l;
	destroy_create_image(m, 0);
}

void	translate_solids_aux(t_mini *m, char c, double n)
{
	if (c == 'f' || c == 'b')
	{
		if (m->s->l == 'P')
			m->s->pl->pos.z += n;
		else if (m->s->l == 'S')
			m->s->sp->pos.z += n;
		else if (m->s->l == 'C')
			m->s->cyl->pos.z += n;
		else if (m->s->l == 'O')
			m->s->co->pos.z += n;
	}
}

void	translate_solids(t_mini *m, char c, double n)
{
	if (m->s->l == 'P' && (c == 'r' || c == 'l'))
		m->s->pl->pos.x += n;
	else if (m->s->l == 'S' && (c == 'r' || c == 'l'))
		m->s->sp->pos.x += n;
	else if (m->s->l == 'C' && (c == 'r' || c == 'l'))
		m->s->cyl->pos.x += n;
	else if (m->s->l == 'O' && (c == 'r' || c == 'l'))
		m->s->co->pos.x += n;
	if (c == 'u' || c == 'd')
	{
		if (m->s->l == 'P')
			m->s->pl->pos.y += n;
		else if (m->s->l == 'S')
			m->s->sp->pos.y += n;
		else if (m->s->l == 'C')
			m->s->cyl->pos.y += n;
		else if (m->s->l == 'O')
			m->s->co->pos.y += n;
	}
	else
		translate_solids_aux(m, c, n);
}

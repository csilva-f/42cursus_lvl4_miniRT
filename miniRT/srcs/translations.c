/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   translations.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csilva-f <csilva-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 11:50:23 by csilva-f          #+#    #+#             */
/*   Updated: 2023/09/24 13:08:16 by csilva-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

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
}

void	cam_translation(t_mini *m, int x, int y, int z)
{
	t_sphere	*t_sp;
	t_cylinder	*t_cyl;
	t_plane		*t_pl;

	t_sp = m->sp;
	t_cyl = m->cyl;
	t_pl = m->plane;
	solid_iteration(m, x, y, z);
	m->sp = t_sp;
	m->cyl = t_cyl;
	m->plane = t_pl;
	destroy_create_image(m);
}

void	translate_solids_2(t_mini *m, char c, int n)
{
	if (c == 'f' || c == 'b')
	{
		if (m->s->l == 'P')
			m->s->pl->pos.z += n;
		else if (m->s->l == 'S')
			m->s->sp->pos.z += n;
		else if (m->s->l == 'C')
			m->s->cyl->pos.z += n;
	}
}

void	translate_solids(t_mini *m, char c)
{
	int	n;

	n = 1;
	if (c == 'l' || c == 'd' || c == 'b')
		n = -1;
	if (c == 'r' || c == 'l')
	{
		if (m->s->l == 'P')
			m->s->pl->pos.x += n;
		else if (m->s->l == 'S')
			m->s->sp->pos.x += n;
		else if (m->s->l == 'C')
			m->s->cyl->pos.x += n;
	}
	else if (c == 'u' || c == 'd')
	{
		if (m->s->l == 'P')
			m->s->pl->pos.y += n;
		else if (m->s->l == 'S')
			m->s->sp->pos.y += n;
		else if (m->s->l == 'C')
			m->s->cyl->pos.y += n;
	}
	else
		translate_solids_2(m, c, n);
}

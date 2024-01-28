/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solid_movs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csilva-f <csilva-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 14:50:09 by csilva-f          #+#    #+#             */
/*   Updated: 2023/09/28 19:24:48 by csilva-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

t_solid	*s_last(t_solid *s)
{
	t_solid	*aux;

	if (!s)
		return (NULL);
	aux = s;
	while (aux->next && aux->next->head != 1)
		aux = aux->next;
	return (aux);
}

void	solid_add_b(t_solid **s, t_solid *s_new)
{
	t_solid	*aux;

	if (s)
	{
		if (*s)
		{
			aux = s_last(*s);
			aux->next = s_new;
			s_new = aux;
		}
		else
		{
			s_new->head = 1;
			*s = s_new;
		}
	}
}

t_solid	*solid_new(t_mini *m, t_plane *p, t_sphere *s, t_cylinder *c)
{
	t_solid	*solid;

	solid = malloc(sizeof(t_solid));
	if (!solid)
		return (NULL);
	solid->head = 0;
	if (p)
	{
		solid->l = 'P';
		solid->pl = p;
	}
	else if (s)
	{
		solid->l = 'S';
		solid->sp = s;
	}
	else if (c)
	{
		solid->l = 'C';
		solid->cyl = c;
	}
	solid->next = m->s;
	return (solid);
}

void	print_solid_list(t_mini *m)
{
	t_solid	*temp;

	temp = m->s;
	while (m->s->head != 1)
		m->s = m->s->next;
	while (m->s->next && m->s->next->head != 1)
		m->s = m->s->next;
	m->s = temp;
}

void	fill_solid_list(t_mini *m)
{
	t_plane		*t_pl;
	t_sphere	*t_sp;
	t_cylinder	*t_cyl;

	t_pl = m->plane;
	t_sp = m->sp;
	t_cyl = m->cyl;
	while (m->plane)
	{
		solid_add_b(&m->s, solid_new(m, m->plane, NULL, NULL));
		m->plane = m->plane->next;
	}
	while (m->sp)
	{
		solid_add_b(&m->s, solid_new(m, NULL, m->sp, NULL));
		m->sp = m->sp->next;
	}
	while (m->cyl)
	{
		solid_add_b(&m->s, solid_new(m, NULL, NULL, m->cyl));
		m->cyl = m->cyl->next;
	}
	m->plane = t_pl;
	m->sp = t_sp;
	m->cyl = t_cyl;
}

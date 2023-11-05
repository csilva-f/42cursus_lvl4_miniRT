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

#include "../includes/miniRT_bonus.h"

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

void	fill_solid_list_aux(t_mini *m)
{
	while (m->cyl)
	{
		solid_add_b(&m->s, solid_new2(m, m->cyl, NULL));
		m->cyl = m->cyl->next;
	}
	while (m->co)
	{
		solid_add_b(&m->s, solid_new2(m, NULL, m->co));
		m->co = m->co->next;
	}
}

void	fill_solid_list(t_mini *m)
{
	t_plane		*t_pl;
	t_sphere	*t_sp;
	t_cylinder	*t_cyl;
	t_cone		*t_co;

	t_pl = m->plane;
	t_sp = m->sp;
	t_cyl = m->cyl;
	t_co = m->co;
	while (m->plane)
	{
		solid_add_b(&m->s, solid_new(m, m->plane, NULL));
		m->plane = m->plane->next;
	}
	while (m->sp)
	{
		solid_add_b(&m->s, solid_new(m, NULL, m->sp));
		m->sp = m->sp->next;
	}
	fill_solid_list_aux(m);
	m->plane = t_pl;
	m->sp = t_sp;
	m->cyl = t_cyl;
	m->co = t_co;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solid_movs_3_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvieira <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 12:08:30 by fvieira           #+#    #+#             */
/*   Updated: 2023/11/05 12:08:32 by fvieira          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT_bonus.h"

t_solid	*solid_new2(t_mini *m, t_cylinder *c, t_cone *o)
{
	t_solid	*solid;

	solid = malloc(sizeof(t_solid));
	if (!solid)
		return (NULL);
	solid->head = 0;
	if (c)
	{
		solid->l = 'C';
		solid->cyl = c;
	}
	else if (o)
	{
		solid->l = 'O';
		solid->co = o;
	}
	solid->next = m->s;
	return (solid);
}

t_solid	*solid_new(t_mini *m, t_plane *p, t_sphere *s)
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
	solid->next = m->s;
	return (solid);
}

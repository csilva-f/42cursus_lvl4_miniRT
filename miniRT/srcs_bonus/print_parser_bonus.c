/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_parser_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csilva-f <csilva-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 21:51:13 by csilva-f          #+#    #+#             */
/*   Updated: 2023/11/09 21:38:33 by csilva-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT_bonus.h"

void	print_parser_aux2(t_mini *m)
{
	t_cone	*co;
	t_light	*l;

	co = m->co;
	l = m->light;
	while (co != NULL)
	{
		printf("co\n%f,%f,%f %f,%f,%f %f %f %i %i %i\n", co->pos.x, co->pos.y, \
				co->pos.z, co->vec.vx, co->vec.vy, co->vec.vz, co->k, co->h, \
				(int)co->color.x, (int)co->color.y, (int)co->color.z);
		co = co->next;
	}
	while (l != NULL)
	{
		printf("L\n%f,%f,%f %f, %i %i %i\n", l->pos.x, l->pos.y, \
			l->pos.z, l->ratio, (int)l->color.x, (int)l->color.y, \
			(int)l->color.z);
		l = l->next;
	}
}

void	print_parser_aux(t_mini *m)
{
	t_sphere	*s;
	t_cylinder	*c;

	s = m->sp;
	c = m->cyl;
	while (s != NULL)
	{
		printf("sp\n%f,%f", s->pos.x, s->pos.y);
		printf(",%f %f, %i %i %i\n", s->pos.z, s->d, (int)s->color.x, \
				(int)s->color.y, (int)s->color.z);
		s = s->next;
	}
	while (c != NULL)
	{
		printf("cy\n%f,%f,%f %f,%f,%f %f %f %i %i %i\n", c->pos.x, c->pos.y, \
				c->pos.z, c->vec.vx, c->vec.vy, c->vec.vz, c->d, c->h, \
				(int)c->color.x, (int)c->color.y, (int)c->color.z);
		c = c->next;
	}
	print_parser_aux2(m);
}

void	print_parser(t_mini *m)
{
	t_plane		*pl;

	printf("A\n%f %i %i %i\n", m->al->ratio, (int)m->al->color.x, \
			(int)m->al->color.y, (int)m->al->color.z);
	printf("C\n%f,%f", m->cam->pos.x, m->cam->pos.y);
	printf(",%f %f,%f,%f %i\n", m->cam->pos.z, \
			m->cam->vec.vx, m->cam->vec.vy, m->cam->vec.vz, m->cam->fov);
	pl = m->plane;
	while (pl != NULL)
	{
		printf("pl\n%f,%f,%f %f,%f,%f %i %i %i\n", pl->pos.x, pl->pos.y, \
				pl->pos.z, pl->vec.vx, pl->vec.vy, pl->vec.vz, \
				(int)pl->color.x, (int)pl->color.y, (int)pl->color.z);
		pl = pl->next;
	}
	print_parser_aux(m);
}

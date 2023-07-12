/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coord_transform.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvieira <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 15:39:09 by fvieira           #+#    #+#             */
/*   Updated: 2023/07/12 15:39:11 by fvieira          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

void	data_transform(t_mini *m)
{
	t_sphere	*temp_sp;
	t_plane		*temp_pl;
	t_cylinder	*temp_cyl;

	temp_sp = m->sp;
	temp_pl = m->plane;
	temp_cyl = m->cyl;
	while(m->sp)
	{
		m->sp->cx -= m->cam->x;
		m->sp->cy -= m->cam->y;
		m->sp->cz -= m->cam->z;
		m->sp = m->sp->next;
	}
	while(m->plane)
	{
		m->plane->x -= m->cam->x;
		m->plane->y -= m->cam->y;
		m->plane->z -= m->cam->z;
		m->plane = m->plane->next;
	}
	while(m->cyl)
	{
		m->cyl->cx -= m->cam->x;
		m->cyl->cy -= m->cam->y;
		m->cyl->cz -= m->cam->z;
		m->cyl = m->cyl->next;
	}
	m->sp = temp_sp;
	m->plane = temp_pl;
	m->cyl = temp_cyl;
	m->cam->x = 0;
	m->cam->y = 0;
	m->cam->z = 0;
}

/*void	eq_transform(t_mini *mini)
{

}

void	data_transform(t_mini *mini)
{
	coord_transform(mini);
	eq_transform(mini);
}*/
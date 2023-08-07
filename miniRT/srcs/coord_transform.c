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
	m->cam->pos.z -= 1;
	while (m->sp)
	{
		m->sp->pos = coord_sub(m->sp->pos, m->cam->pos);
		m->sp = m->sp->next;
	}
	while (m->plane)
	{
		m->plane->pos = coord_sub(m->plane->pos, m->cam->pos);
		m->plane = m->plane->next;
	}
	while (m->cyl)
	{
		m->cyl->pos = coord_sub(m->cyl->pos, m->cam->pos);
		m->cyl = m->cyl->next;
	}
	m->sp = temp_sp;
	m->plane = temp_pl;
	m->cyl = temp_cyl;
	m->cam->pos.x = 0;
	m->cam->pos.y = 0;
	m->cam->pos.z = -1;
}

/*void	eq_transform(t_mini *mini)
{

}

void	data_transform(t_mini *mini)
{
	coord_transform(mini);
	eq_transform(mini);
}*/
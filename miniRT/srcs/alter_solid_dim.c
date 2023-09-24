/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alter_solid_dim.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csilva-f <csilva-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 23:17:29 by csilva-f          #+#    #+#             */
/*   Updated: 2023/09/24 13:00:20 by csilva-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

void	reset_canvas(t_mini *m, int r, int inc)
{
	t_sphere	*temp_s;

	temp_s = m->sp;
	if (!r)
	{
		while (m->sp)
		{
			m->sp->d = m->sp->d + inc * m->sp->d * 0.1;
			m->sp->d_squared = m->sp->d * m->sp->d_squared;
			m->sp = m->sp->next;
		}
		m->sp = temp_s;
	}
	else
	{
		free_structs(m, 0);
		init(m);
		get_values(m);
	}
	destroy_create_image(m);
}

void	cyl_height_diam(t_mini *m, int d_inc, int h_inc, t_cylinder *t_c)
{
	t_c = m->cyl;
	if (d_inc != 0)
	{
		while (m->cyl)
		{
			m->cyl->d = m->cyl->d + d_inc * 0.1 * m->cyl->d;
			m->cyl->d_squared = m->cyl->d * m->cyl->d;
			m->cyl = m->cyl->next;
		}
	}
	else
	{
		while (m->cyl)
		{
			m->cyl->h = m->cyl->h + h_inc * 0.1 * m->cyl->h;
			m->cyl = m->cyl->next;
		}
	}
	m->cyl = t_c;
	destroy_create_image(m);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phong_2_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csilva-f <csilva-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 15:00:33 by csilva-f          #+#    #+#             */
/*   Updated: 2023/11/26 16:43:53 by csilva-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT_bonus.h"

void	collisions_aux3(t_mini *m, t_ray *ray)
{
	while (m->co)
	{
		cone_collision(m->co, ray, NULL, (t_vector){0, 0, 0});
		m->co = m->co->next;
		if (ray->t >= 0.0005)
			return ;
	}
}

void	collisions_aux2(t_mini *m, t_ray *ray)
{
	while (m->sp)
	{
		if (m->sp->b1 || m->sp->b2)
			sphere_collision_bump(m->sp, ray);
		else
			sphere_collision(m->sp, ray);
		m->sp = m->sp->next;
		if (ray->t >= 0.0005)
			return ;
	}
	while (m->plane)
	{
		plane_collision(m->plane, ray, 0, 0);
		m->plane = m->plane->next;
		if (ray->t >= 0.0005)
			return ;
	}
	while (m->cyl)
	{
		cylinder_collision(m->cyl, ray);
		m->cyl = m->cyl->next;
		if (ray->t >= 0.0005)
			return ;
	}
	collisions_aux3(m, ray);
}

void	light_collisions(t_mini *m, t_ray *temp)
{
	t_sphere	*temp_sp;
	t_plane		*temp_pl;
	t_cylinder	*temp_cyl;
	t_cone		*temp_co;

	temp_pl = m->plane;
	temp_sp = m->sp;
	temp_cyl = m->cyl;
	temp_co = m->co;
	collisions_aux2(m, temp);
	m->plane = temp_pl;
	m->sp = temp_sp;
	m->cyl = temp_cyl;
	m->co = temp_co;
}

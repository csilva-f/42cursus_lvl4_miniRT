/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csilva-f <csilva-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/01 12:10:03 by csilva-f          #+#    #+#             */
/*   Updated: 2023/10/01 12:35:27 by csilva-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

t_vector	rotation_axis(char c)
{
	t_vector	axis;

	if (c == 'x')
		axis = (t_vector){1, 0, 0};
	else if (c == 'y')
		axis = (t_vector){0, 1, 0};
	else if (c == 'z')
		axis = (t_vector){0, 0, 1};
	else
		axis = (t_vector){0, 0, 0};
	return (axis);
}

void	cam_rotation(t_mini *m, char c)
{
	t_sphere	*t_sp;
	t_cylinder	*t_cyl;
	t_plane		*t_pl;
	t_light		*t_l;

	t_l = m->light;
	t_sp = m->sp;
	t_cyl = m->cyl;
	t_pl = m->plane;
	m->cam->vec = rotate_vector(m->cam->vec, rotation_axis(c), 15);
	//data_transform(m);
	destroy_create_image(m, 0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csilva-f <csilva-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 14:44:12 by csilva-f          #+#    #+#             */
/*   Updated: 2023/07/09 15:33:39 by csilva-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <fcntl.h>
# include <math.h>
# include "../libft/libft.h"

typedef struct	s_al
{
	float	ratio;
	int		color;
}		t_al;

typedef	struct	s_cam
{
	float	x;
	float	y;
	float	z;
	float	ov_x;
	float	ov_y;
	float	ov_z;
	int		fov;
}		t_cam;

typedef struct	s_light
{
	float	x;
	float	y;
	float	z;
	float	ratio;
	int		color;
}		t_light;

typedef struct	s_sphere
{
	float	cx;
	float	cy;
	float	cz;
	float	d;
	int		color;
}		t_sphere;

typedef struct	s_plane
{
	float	x;
	float	y;
	float	z;
	float	nv_x;
	float	nv_y;
	float	nv_z;
	int		color;
}		t_plane;

typedef struct	s_cylinder
{
	float	cx;
	float	cy;
	float	cz;
	float	nv_x;
	float	nv_y;
	float	nv_z;
	float	d;
	float	h;
	int		color;
}		t_cylinder;

typedef struct	s_mini
{
	char		*file;
	int			fd;
	int			is_valid;
	t_al		*al;
	t_cam		*cam;
	t_light		*light;
	t_sphere	*sp;
	t_plane		*plane;
	t_cylinder	*cyl;
}		t_mini;

//-------------------------------------SRCS-------------------------------------
// CHECK
int		error_handler(int is_valid, int code);
int		check_file(char *file_name, t_mini *mini);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csilva-f <csilva-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 14:44:12 by csilva-f          #+#    #+#             */
/*   Updated: 2023/07/11 00:12:22 by csilva-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <fcntl.h>
# include <math.h>
# include "../libft/libft.h"

typedef struct s_al
{
	float	ratio;
	int		color;
}		t_al;

typedef struct s_cam
{
	float	x;
	float	y;
	float	z;
	float	ov_x;
	float	ov_y;
	float	ov_z;
	int		fov;
}		t_cam;

typedef struct s_light
{
	float	x;
	float	y;
	float	z;
	float	ratio;
	int		color;
}		t_light;

typedef struct s_sphere
{
	float			cx;
	float			cy;
	float			cz;
	float			d;
	int				color;
	struct s_sphere	*next;
	struct s_sphere	*prev;
}		t_sphere;

typedef struct s_plane
{
	float			x;
	float			y;
	float			z;
	float			nv_x;
	float			nv_y;
	float			nv_z;
	int				color;
	struct s_plane	*next;
	struct s_plane	*prev;
}		t_plane;

typedef struct s_cylinder
{
	float				cx;
	float				cy;
	float				cz;
	float				nv_x;
	float				nv_y;
	float				nv_z;
	float				d;
	float				h;
	int					color;
	struct s_cylinder	*next;
	struct s_cylinder	*prev;
}		t_cylinder;

typedef struct s_mini
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
int			error_handler(int is_valid, int code);
int			check_file(char *file_name, t_mini *mini);
void		vars_errors(t_mini *mini, int code);

// COLORS

int			rgb_to_int(int red, int green, int blue);
int			fill_colors(t_mini *m, char *str, int c);

// FILE READER

void		check_identifier(char *str);
void		check_line_values(t_mini *mini, char **vars);
void		check_lines(t_mini *mini, char *aux);
void		get_values(t_mini *mini);
void		print_parser(t_mini *m);

// LIGHTS & CAMERA

void		check_a_vars(t_mini *m, char **vars);
void		check_c_vars(t_mini *m, char **v, char **data);
void		check_l_vars(t_mini *m, char **vars);

// SHAPES

void		check_pl_vars(t_mini *m, char **vars);
void		check_sp_vars(t_mini *m, char **vars);
void		check_cy_vars(t_mini *m, char **vars);

t_plane		*pl_new(t_mini *m, char **vars, char ***data);
t_plane		*pl_last(t_plane *pl);
void		pl_add_b(t_plane **pl, t_plane *pl_new);
t_sphere	*sph_new(t_mini *m, char **vars, char ***data);
t_sphere	*sph_last(t_sphere *sp);
void		sph_add_b(t_sphere **sp, t_sphere *sp_new);
t_cylinder	*cy_new(t_mini *m, char **vars, char ***data);
t_cylinder	*cy_last(t_cylinder *cy);
void		cy_add_b(t_cylinder **cy, t_cylinder *cy_new);

// TRANSFORMATION

void	data_transform(t_mini *m);

// AUXIL

int			count_vars(char **vars, int equal, int code, t_mini *m);
float		float_check(t_mini *m, char *str);

#endif

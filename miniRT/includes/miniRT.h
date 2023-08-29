/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csilva-f <csilva-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 14:44:12 by csilva-f          #+#    #+#             */
/*   Updated: 2023/08/29 21:22:58 by csilva-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <string.h>
# include <fcntl.h>
# include <math.h>
# include "../libft/libft.h"
# include "../coords_vectors/coords_vectors.h"
# include "../mlx_linux/mlx.h"

# define HEIGHT 72
# define WIDTH 128

# define ESC 65307

# define LEFT 65361
# define UP 65362
# define RIGHT 65363
# define DOWN 65364
# define R 114
# define Z 122
# define PLUS 65451
# define MINUS 65453

typedef struct s_al
{
	float	ratio;
	int		color;
}		t_al;

typedef struct s_cam
{
	t_pos		pos;
	t_vector	vec;
	int			fov;
}		t_cam;

typedef struct s_light
{
	t_pos	pos;
	float	ratio;
	int		color;
}		t_light;

typedef struct s_ray
{
	t_pos			p0;
	t_vector		v1;
	t_vector		norm_v;
	float			sqrt_len;
	float			t;
	int				reflex_times;
	int				color;
	struct s_ray	*next;
	struct s_ray	*prev;
}		t_ray;

typedef struct s_sphere
{
	t_pos			pos;
	float			d;
	float			d_squared;
	int				color;
	struct s_sphere	*next;
	struct s_sphere	*prev;
}		t_sphere;

typedef struct s_plane
{
	t_pos			pos;
	t_vector		vec;
	float			coef;
	int				color;
	struct s_plane	*next;
	struct s_plane	*prev;
}		t_plane;

typedef struct s_cylinder
{
	t_pos				pos;
	t_vector			vec;
	float				d;
	float				d_squared;
	float				h;
	int					color;
	struct s_cylinder	*next;
	struct s_cylinder	*prev;
}		t_cylinder;

typedef struct s_graphics
{
	void	*img;
	void	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	void	*mlx;
	void	*win;
	int		width;
	int		height;
}		t_graphics;

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
	t_ray		*ray;
	t_graphics	*g;
}		t_mini;

//-------------------------------------SRCS-------------------------------------

// CHECK
bool		error_handler(int is_valid, int code);
void		vars_errors(t_mini *mini, int code);
bool		check_file(char *file_name, t_mini *mini);

// CLEAR
void		free_solids(t_mini *mini);
void		free_structs(t_mini *mini);

// COLLISIONS
float		quadratic_form(float a, float b, float c);
bool		sphere_collision(t_sphere *sp, t_ray *r);
bool		cylinder_collision(t_cylinder *c, t_ray *r);
bool		plane_collision(t_plane *pl, t_ray *r1);

// COLORS
int			rgb_to_int(int red, int green, int blue);
int			fill_colors(t_mini *m, char *str, int c);

// COORD TRANSFORMATION
void		data_transform(t_mini *m);

// INITIALIZE
void		init(t_mini *mini);
void		init_canvas(t_mini *m);

// FILE READER
int			check_identifier(char *str);
void		check_line_values(t_mini *mini, char **vars);
void		check_lines(t_mini *mini, char *aux);
void		get_values(t_mini *mini);
void		print_parser(t_mini *m);

// LIGHTRAYS
t_pos		ray_pos(t_pos p, t_vector v, float t);
t_ray		*ray_new(t_pos p, t_vector v);
void		collisions_aux(t_mini *m);
void		collisions(t_mini *m, int x, int y);
void		ray_create(t_mini *m);

// LIGHTS & CAMERA
void		check_a_vars(t_mini *m, char **vars);
int			counter_c(t_mini *m);
void		check_c_vars(t_mini *m, char **v, char **data);
void		check_l_vars(t_mini *m, char **vars);

// MLX
int			my_mlx_pixel_put(t_mini *m, int x, int y, int color);
int			close_game(t_mini *m);
int			key_hook(int keycode, t_mini *m);
void		raytracing(t_mini *m);
void		start_mlx(t_mini *m);

// PIXEL CAMERA
float		pixel_cam_x(float psx, t_mini *m);
float		pixel_cam_y(float psy, t_mini *m);
t_pos		pixel_pos(float psx, float psy, t_mini *m);
t_vector	pixel_vec(t_pos pix);

// REFLECTION
t_vector	reflected_ray(t_ray *r);

// SHAPE CHECKER
void		check_pl_vars(t_mini *m, char **vars);
void		check_sp_vars(t_mini *m, char **vars);
void		check_cy_vars(t_mini *m, char **vars);

// SOLID LST
t_plane		*pl_new(t_mini *m, char **vars, char ***data);
t_plane		*pl_last(t_plane *pl);
void		pl_add_b(t_plane **pl, t_plane *pl_new);
t_sphere	*sph_new(t_mini *m, char **vars, char ***data);
t_sphere	*sph_last(t_sphere *sp);

// SOLID LST 2
void		sph_add_b(t_sphere **sp, t_sphere *sp_new);
t_cylinder	*cy_new(t_mini *m, char **vars, char ***data);
t_cylinder	*cy_last(t_cylinder *cy);
void		cy_add_b(t_cylinder **cy, t_cylinder *cy_new);

// MAIN
int			count_vars(char **vars, int equal, int code, t_mini *m);
float		float_check(t_mini *m, char *str);

#endif

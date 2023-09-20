/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csilva-f <csilva-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 14:44:12 by csilva-f          #+#    #+#             */
/*   Updated: 2023/09/20 23:19:23 by csilva-f         ###   ########.fr       */
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

# ifdef __APPLE__
#  include "../mlx_macos/mlx.h"
# else
#  include "../mlx_linux/mlx.h"
#  include <X11/X.h>
# endif

# define HEIGHT 72
# define WIDTH 128

# define ESC 65307
# define LEFT 65361
# define UP 65362
# define RIGHT 65363
# define DOWN 65364
# define TR 114
# define TZ 122
# define TM 109
# define S 115
# define T1 65436
# define T2 65433
# define T3 65435
# define T4 65430
# define T5 65437
# define T6 65432
# define T7 65429
# define T8 65431
# define T9 65434
# define T0 65438
# define PLUS 65451
# define MINUS 65453

# define WHITE 0xFFFFFF
# define YELLOW 0xFFCF40
# define BLUE 0x80A0CC

typedef struct s_al
{
	float	ratio;
	t_pos	color;
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
	t_pos	color;
}		t_light;

typedef struct s_ray
{
	t_pos			p0;
	t_vector		v1;
	t_vector		norm_v;
	float			sqrt_len;
	float			t;
	int				reflex_times;
	t_pos			color;
	struct s_ray	*next;
	struct s_ray	*prev;
}		t_ray;

typedef struct s_sphere
{
	t_pos			pos;
	float			d;
	float			d_squared;
	t_pos			color;
	struct s_sphere	*next;
	struct s_sphere	*prev;
}		t_sphere;

typedef struct s_plane
{
	t_pos			pos;
	t_vector		vec;
	float			coef;
	t_pos			color;
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
	t_pos				color;
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
	void	*menu_mlx;
	void	*menu_win;
	void	*menu_img;
	int		width;
	int		height;
}		t_graphics;

typedef struct s_mini
{
	char		*file;
	int			fd;
	int			is_valid;
	int			counter_a;
	int			counter_c;
	int			counter_l;
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

// ALTER SOLID DIMENSIONS
void		reset_canvas(t_mini *m, int r, int inc);
void		cyl_height_diam(t_mini *m, int d_inc, int h_inc, t_cylinder *t_c);

// CHECK
bool		error_handler(int is_valid, int code);
void		vars_errors(t_mini *mini, int code);
bool		check_file(char *file_name, t_mini *mini);

// CLEAR
void		free_solids(t_mini *mini);
void		free_structs(t_mini *mini, int mlx);

// COLLISIONS
float		quadratic_form(float a, float b, float c);
bool		sphere_collision(t_sphere *sp, t_ray *r);
void		bases_aux(t_cylinder *c, float b, t_pos *p, t_vector *v);
void		bases_aux_2(t_ray *r, t_vector v, float *n_d);
bool		bases(t_cylinder *c, t_ray *r, float base, float t);

// COLLISIONS 2
float		*cyl_collision_aux(t_cylinder *c, t_ray *r, t_vector *x);
void		cyl_collision_aux2(t_cylinder *c, t_ray *r, float *d, t_vector x);
bool		cylinder_collision(t_cylinder *c, t_ray *r);
bool		plane_collision(t_plane *pl, t_ray *r1);

// COLORS
int			rgb_to_int(int red, int green, int blue);
void		fill_colors(t_mini *m, char *str, t_pos *col);

// COLOR_OP
t_pos		multconst_rgb(float c, t_pos color);
t_pos		multiply_rgb(t_pos color1, t_pos color2);
t_pos		add_rgb(t_pos color1, t_pos color2);
t_pos		sub_rgb(t_pos color1, t_pos color2);
t_pos		divide_rgb(t_pos color1, t_pos color2);

// COORD TRANSFORMATION
void		data_transform_aux(t_mini *m);
void		data_transform(t_mini *m);

// INITIALIZE
void		init(t_mini *mini);
void		init_canvas(t_mini *m);

// FILE READER
int			check_identifier(char *str);
void		check_line_values(t_mini *mini, char **vars);
void		check_lines(t_mini *mini, char *aux);
void		get_values(t_mini *mini);

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

// MENU
void		create_menu(t_mini *m);

// MLX
int			my_mlx_pixel_put(t_mini *m, int x, int y, t_pos c);
int			close_game(t_mini *m);
int			key_hook(int keycode, t_mini *m);
void		raytracing(t_mini *m);
//void		start_mlx(t_mini *m);

// PIXEL CAMERA
float		pixel_cam_x(float psx, t_mini *m);
float		pixel_cam_y(float psy, t_mini *m);
t_pos		pixel_pos(float psx, float psy, t_mini *m);
t_vector	pixel_vec(t_pos pix);

// REFLECTION
t_vector	reflected_ray(t_ray *r, t_vector l);

// PHONG
t_pos		phong(t_mini *m, t_ray *r, bool diffuse);//, float alpha);
bool		shadow(t_mini *m, t_ray *ray);

// PRINT
void		print_parser(t_mini *m);

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
void		cy_new_aux(t_mini *m, char ***data, t_cylinder **c);
t_cylinder	*cy_new(t_mini *m, char **vars, char ***data);
t_cylinder	*cy_last(t_cylinder *cy);
void		cy_add_b(t_cylinder **cy, t_cylinder *cy_new);

// MAIN
int			count_vars(char **vars, int equal, int code, t_mini *m);
float		float_check(t_mini *m, char *str);

#endif

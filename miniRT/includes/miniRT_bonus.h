/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT_bonus.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csilva-f <csilva-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 14:44:12 by csilva-f          #+#    #+#             */
/*   Updated: 2023/10/23 19:35:47 by csilva-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_BONUS_H
# define MINIRT_BONUS_H

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

# define HEIGHT 72.0/4
# define WIDTH 128.0/4

# define ESC 65307
# define LEFT 65361
# define UP 65362
# define RIGHT 65363
# define DOWN 65364
# define PLUS 65451
# define MINUS 65453
# define R 114
# define X 120
# define Y 121
# define Z 122
# define M 109
# define S 115
# define F 98
# define B 102
# define T 116
# define I 105
# define D 100
# define H 104
# define L 108
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

# define PI 3.1415926
/*# define YELLOW 0xFFFF00
# define BLUE 0x00FFFF*/

typedef struct s_al
{
	double	ratio;
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
	t_pos			pos;
	double			ratio;
	t_pos			color;
	t_vector		orig;
	struct s_light	*next;
}		t_light;

typedef struct s_ray
{
	t_pos			p0;
	t_vector		v1;
	t_vector		norm_v;
	double			sqrt_len;
	double			t;
	int				reflex_times;
	t_pos			color;
	struct s_ray	*next;
	struct s_ray	*prev;
}		t_ray;

typedef struct s_sphere
{
	t_pos			pos;
	double			d;
	double			d_squared;
	t_pos			color;
	t_vector		orig;
	struct s_sphere	*next;
	struct s_sphere	*prev;
}		t_sphere;

typedef struct s_plane
{
	t_pos			pos;
	t_vector		vec;
	double			coef;
	t_vector		orig;
	t_pos			color;
	struct s_plane	*next;
	struct s_plane	*prev;
}		t_plane;

typedef struct s_cylinder
{
	t_pos				pos;
	t_vector			vec;
	double				d;
	double				d_squared;
	double				h;
	t_vector			orig;
	t_pos				color;
	struct s_cylinder	*next;
	struct s_cylinder	*prev;
}		t_cylinder;

typedef struct s_cone
{
	t_pos				pos;
	t_vector			vec;
	double				k;
	double				k_k;
	double				h;
	t_vector			orig;
	t_pos				color;
	struct s_cone		*next;
	struct s_cone		*prev;
}		t_cone;

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

typedef struct s_solid
{
	bool			head;
	char			l;
	t_plane			*pl;
	t_sphere		*sp;
	t_cylinder		*cyl;
	t_cone			*co;
	t_pos			old_color;			
	struct s_solid	*next;
}		t_solid;

typedef struct s_angles
{
	double			teta;
	double			fi;
	double			psi;
}		t_angles;

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
	t_cone		*co;
	t_ray		*ray;
	t_graphics	*g;
	t_solid		*s;
	bool		hl;
	t_pos		grey_c;
	char		action;
	bool		reset;
	bool		flag;
	bool		init;
}		t_mini;

//-------------------------------------SRCS-------------------------------------

// ALTER SOLID DIMENSIONS
void		reset_canvas(t_mini *m);
void		solids_dimensions(t_mini *m, char c);

// ANGLES CALCULATE
t_angles	three_d_angles(t_vector a, t_vector b);

// CHECK
bool		error_handler(int is_valid, int code);
void		vars_errors(t_mini *mini, int code);
bool		check_file(char *file_name, t_mini *mini);

// CLEAR
void		free_solids_2(t_mini *m);
void		free_solids(t_mini *mini);
void		free_structs(t_mini *mini, int mlx);

// COLLISIONS
double		quadratic_form(double a, double b, double c);
bool		sphere_collision(t_sphere *sp, t_ray *r);
void		bases_aux_2(t_ray *r, t_vector v);
double		bases_aux(double *n, t_pos *pos, t_vector *vec, t_cylinder *c);
double		bases(t_cylinder *c, t_ray *r, double t);

// COLLISIONS 2
void		cyl_collision_aux(double *d, t_cylinder *c, t_ray *r, t_vector *x);
void		cyl_collision_aux2(t_cylinder *c, t_ray *r, double *d, t_vector x);
bool		cylinder_collision(t_cylinder *c, t_ray *r);
bool		plane_collision(t_plane *pl, t_ray *r1);
bool		cone_collision(t_cone *co, t_ray *r);

// COLOR_OP
t_pos		multconst_rgb(double c, t_pos color);
t_pos		multiply_rgb(t_pos color1, t_pos color2);
t_pos		add_rgb(t_pos color1, t_pos color2);
t_pos		sub_rgb(t_pos color1, t_pos color2);
t_pos		divide_rgb(t_pos color1, t_pos color2);

// COLORS
int			rgb_to_int(int red, int green, int blue);
void		fill_colors(t_mini *m, char *str, t_pos *col);

// COORD TRANSFORMATION
t_vector	rotate_vector_aux(double angle, t_vector axis, t_vector v);
t_vector	rotate_vector_2(t_mini *m, t_vector v, t_vector axis, double angle);
void		data_transform_aux_2(t_mini *m, double angle, t_vector axis, t_pos o);
void		data_transform_aux(t_mini *m, double a, t_pos o, t_vector axis_of_rot);
void		data_transform(t_mini *m);

// COORD TRANSFORMATION 2
t_vector	eq_transform(t_mini *m, double *angle);

// FILE READER
int			check_identifier(char *str);
void		check_line_values(t_mini *mini, char **vars);
void		check_lines(t_mini *mini, char *aux);
void		get_values(t_mini *mini);

// INITIALIZE
void		init(t_mini *mini);
void		init_canvas(t_mini *m);

//KEY HOOK
void		key_hook_aux_3(int keycode, t_mini *m);
void		key_hook_aux_2(int keycode, t_mini *m);
void		key_hook_dim_rot_tr(int k, t_mini *m);
void		key_hook_aux(int keycode, t_mini *m);
int			key_hook(int keycode, t_mini *m);

// LIGHTRAYS
t_pos		ray_pos(t_pos p, t_vector v, double t);
t_ray		*ray_new(t_pos p, t_vector v);
void		collisions_aux(t_mini *m, t_ray *ray);
void		collisions(t_mini *m, int x, int y);
void		ray_create(t_mini *m);

// LIGHTS & CAMERA
void		check_a_vars(t_mini *m, char **vars);
int			counter_c(t_mini *m);
void		check_c_vars(t_mini *m, char **v, char **data);
void		check_l_vars(t_mini *m, char **vars);

// MENU
void		create_menu_aux(int y, void *mlx, void *win);
void		create_menu(t_mini *m);

// MLX
int			my_mlx_pixel_put(t_mini *m, int x, int y, t_pos c);
int			close_game(t_mini *m);
void		print_action(t_mini *m, int action);
void		destroy_create_image(t_mini *m, int action);
void		raytracing(t_mini *m);

// PHONG
t_pos		phong(t_mini *m, t_ray *r, bool diffuse);//, double alpha);
bool		shadow(t_mini *m);

// PIXEL CAMERA
double		pixel_cam_x(double psx, t_mini *m);
double		pixel_cam_y(double psy, t_mini *m);
t_pos		pixel_pos(double psx, double psy, t_mini *m);
t_vector	pixel_vec(t_pos pix);

// PRINT
void		print_parser_aux(t_mini *m);
void		print_parser(t_mini *m);

// REFLECTION
t_vector	reflected_ray(t_ray *r, t_vector l);

// ROTATION
t_vector	rotation_axis(char c);
t_vector	rotation_matrix(char c, t_vector v, double angle, double *n);
t_vector	vector_origin(t_vector v, t_pos o, int sub);
void		cam_rotation_aux(t_mini *m, char c, double *n);
void		cam_rotation(t_mini *m, char c, double *n);

// SHAPE CHECKER
void		check_pl_vars(t_mini *m, char **vars);
void		check_sp_vars(t_mini *m, char **vars);
void		check_cy_vars(t_mini *m, char **vars);
void		check_co_vars(t_mini *m, char **vars);

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

// SOLID LST 3
void		co_add_b(t_cone **cone, t_cone *co_new);
t_cone		*co_last(t_cone *cone);
t_cone		*co_new(t_mini *m, char **vars, char ***data);
void		co_new_aux(t_mini *m, char ***data, t_cone **c);
// SOLID MOVEMENTS
t_solid		*s_last(t_solid *s);
void		solid_add_b(t_solid **s, t_solid *s_new);
t_solid		*solid_new(t_mini *m, t_plane *p, t_sphere *s, t_cylinder *c, t_cone *co);
void		print_solid_list(t_mini *m);
void		fill_solid_list(t_mini *m);

// SOLID MOVEMENTS 2
void		highlight_solid(t_mini *m);
void		apply_action_iterate(t_mini *m, int iter);
void		init_hl_mode(t_mini *m, int action);
int			def_tip_action(t_mini *m, int action);
void		dim_rot_trans(t_mini *m, int action, int iter, char c);

//SOLID ROTATION
t_vector	rotate_vector(t_vector orig, t_vector axis, double angle);
t_vector	rotate_vector_x(t_vector orig, double angle);
t_vector	rotate_vector_y(t_vector orig, double angle);
t_vector	rotate_vector_z(t_vector orig, double angle);
void		rotate_solids(t_mini *m, char c);

// TRANSLATION
void		solid_iteration(t_mini *m, int x, int y, int z);
void		cam_translation(t_mini *m, int x, int y, int z);
void		translate_solids(t_mini *m, char c, double n);
void		light_translation(t_mini *m, int x, int y, int z);

// MAIN
int			count_vars(char **vars, int equal, int code, t_mini *m);
double		float_check(t_mini *m, char *str);

#endif

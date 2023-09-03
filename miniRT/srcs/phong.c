/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phong.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvieira <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 16:42:32 by fvieira           #+#    #+#             */
/*   Updated: 2023/09/03 16:42:34 by fvieira          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"


/*

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

*/

//para mandatory so temos uma luz por isso vou assumir isso
//depois temos de alterar no bonus pq podemos ter varias e nao deve ser dificil

int	phong(t_mini *m, t_ray *r)
{
	float		i;
	float		k_a;
	float		k_d;
	float		k_s;
	float		alpha;
	t_vector	l;

	k_a = 1;
	k_s = 1;
	k_d = 1;
	alpha = 1;
	l = vector_create(m->light->pos, ray_pos(r->p0, r->v1, r->t));
	i = k_a * m->al->color + k_d * vector_dot(l, r->norm_v) * m->light->color \
	+ k_s * pow(vector_dot(reflected_ray(r, l), vector_mult_const(vector_create(ray_pos(r->p0, r->v1, r->t), coord_new(0, 0, -1)), -1)), alpha);
	return (i);
}

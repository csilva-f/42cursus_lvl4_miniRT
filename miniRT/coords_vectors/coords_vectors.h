/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csilva-f <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 10:07:17 by csilva-f          #+#    #+#             */
/*   Updated: 2023/07/09 19:57:07 by csilva-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COORDS_VECTORS_H
# define COORDS_VECTORS_H

# include <math.h>

typedef struct s_pos
{
	float	x;
	float	y;
	float	z;
}			t_pos;

typedef struct s_vector
{
	float	vx;
	float	vy;
	float	vz;
}			t_vector;

// COORDINATES

t_pos		coord_add(t_pos c1, t_pos c2);
t_pos		coord_sub(t_pos c1, t_pos c2);
t_pos		coord_mult_const(t_pos c1, float c);
float		distance(t_pos p1, t_pos p2);

// VECTORS

float		length(t_vector v1);
t_vector	vector_norm(t_vector v);
t_vector	vector_mult_const(t_vector v1, float c);
t_vector	vector_add(t_vector v1, t_vector v2);
t_vector	vector_sub(t_vector v1, t_vector v2);
t_vector	vector_cross(t_vector v1, t_vector v2);
float		vector_dot(t_vector v1, t_vector v2);
t_vector	vector_create(t_pos p1, t_pos p2);

// MIX

t_pos		vector_to_pos(t_vector v1);
t_vector	pos_to_vector(t_pos p1);

#endif

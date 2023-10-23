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
	double	x;
	double	y;
	double	z;
}			t_pos;

typedef struct s_vector
{
	double	vx;
	double	vy;
	double	vz;
}			t_vector;

// COORDINATES

t_pos		coord_add(t_pos c1, t_pos c2);
t_pos		coord_new(double c1, double c2, double c3);
t_pos		coord_sub(t_pos c1, t_pos c2);
t_pos		coord_mult_const(t_pos c1, double c);
double		distance(t_pos p1, t_pos p2);

// VECTORS

double		length(t_vector v1);
t_vector	vector_norm(t_vector v);
t_vector	vector_mult_const(t_vector v1, double c);
t_vector	vector_add(t_vector v1, t_vector v2);
t_vector	vector_sub(t_vector v1, t_vector v2);
t_vector	vector_cross(t_vector v1, t_vector v2);
double		vector_dot(t_vector v1, t_vector v2);
t_vector	vector_create(t_pos p1, t_pos p2);
t_vector	vector_new(double c1, double c2, double c3);

// MIX

t_pos		vector_to_pos(t_vector v1);
t_vector	pos_to_vector(t_pos p1);

#endif

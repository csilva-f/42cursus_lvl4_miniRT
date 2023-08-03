/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reflection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvieira <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 16:58:19 by fvieira           #+#    #+#             */
/*   Updated: 2023/08/02 16:58:20 by fvieira          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

/*
typedef struct s_ray
{
	t_pos			p0;
	t_vector		v1;
	t_vector		norm_v;
	int				reflex_times;
	struct s_ray	*next;
	struct s_ray	*prev;
}		t_ray;
*/

t_vector	reflected_ray(t_ray *r)
{
	float	dot_product;

	dot_product = 2 * vector_dot(r->v1, r->norm_v);
	return (vector_sub(r->v1, vector_mult_const(r->norm_v, dot_product)));
}

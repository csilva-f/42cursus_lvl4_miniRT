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

#include "../includes/miniRT_bonus.h"

t_vector	reflected_ray(t_ray *r, t_vector l)
{
	float	dot_product;

	dot_product = 2 * vector_dot(l, r->norm_v);
	return (vector_sub(vector_mult_const(r->norm_v, dot_product), l));
}

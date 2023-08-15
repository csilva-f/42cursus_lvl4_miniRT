/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_op3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvieira <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 15:36:43 by fvieira           #+#    #+#             */
/*   Updated: 2023/08/13 15:36:44 by fvieira          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "coords_vectors.h"

t_vector	vector_new(float c1, float c2, float c3)
{
	t_vector	novo;

	novo.vx = c1;
	novo.vy = c2;
	novo.vz = c3;
	return (novo);
}

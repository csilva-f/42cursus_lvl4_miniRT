/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coord_op.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvieira <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 16:54:06 by fvieira           #+#    #+#             */
/*   Updated: 2023/07/14 16:54:08 by fvieira          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "coords_vectors.h"

t_pos	coord_add(t_pos c1, t_pos c2)
{
	t_pos	novo;

	novo.x = c1.x + c2.x;
	novo.y = c1.y + c2.y;
	novo.z = c1.z + c2.z;
	return (novo);
}

t_pos	coord_sub(t_pos c1, t_pos c2)
{
	t_pos	novo;

	novo.x = c1.x - c2.x;
	novo.y = c1.y - c2.y;
	novo.z = c1.z - c2.z;
	return (novo);
}

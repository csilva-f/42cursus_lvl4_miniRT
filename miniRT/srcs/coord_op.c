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

#include "../includes/miniRT.h"

t_pos	coord_add(t_pos c1, t_pos c2)
{
	t_pos	new;

	new.x = c1.x + c2.x;
	new.y = c1.y + c2.y;
	new.z = c1.z + c2.z;
	return (new);
}

t_pos	coord_sub(t_pos c1, t_pos c2)
{
	t_pos	new;

	new.x = c1.x - c2.x;
	new.y = c1.y - c2.y;
	new.z = c1.z - c2.z;
	return (new);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   translations_2_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csilva-f <csilva-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 23:13:46 by csilva-f          #+#    #+#             */
/*   Updated: 2023/11/07 23:14:09 by csilva-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT_bonus.h"

void	light_translation(t_mini *m, int x, int y, int z)
{
	m->light->pos.x += x * 1;
	m->light->pos.y += y * 1;
	m->light->pos.z += z * 1;
	destroy_create_image(m, 5);
}

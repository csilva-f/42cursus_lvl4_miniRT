/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solid_lst_4_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csilva-f <csilva-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 12:38:26 by csilva-f          #+#    #+#             */
/*   Updated: 2023/11/11 12:38:49 by csilva-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT_bonus.h"

void	co_add_b(t_cone **cone, t_cone *co_new)
{
	t_cone	*aux;

	if (cone)
	{
		if (*cone)
		{
			aux = co_last(*cone);
			aux->next = co_new;
			co_new = aux;
		}
		else
			*cone = co_new;
	}
}

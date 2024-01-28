/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_lst_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csilva-f <csilva-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 20:53:52 by csilva-f          #+#    #+#             */
/*   Updated: 2023/11/11 18:30:43 by csilva-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT_bonus.h"

t_light	*light_new(t_mini *m, char **vars, char ***data)
{
	t_light	*l;

	l = malloc(sizeof(t_light));
	if (!l)
		return (NULL);
	l->pos.x = float_check(m, (*data)[0]);
	l->pos.y = float_check(m, (*data)[1]);
	l->pos.z = float_check(m, (*data)[2]);
	l->f = 0;
	if (m->is_valid)
	{
		l->ratio = float_check(m, vars[2]);
		if (l->ratio < 0 || l->ratio > 1)
			vars_errors(m, 4);
		else
			fill_colors(m, vars[3], &l->color);
		l->next = NULL;
	}
	l->next = NULL;
	return (l);
}

t_light	*l_last(t_light *l)
{
	t_light	*aux;

	if (!l)
		return (NULL);
	aux = l;
	while (aux->next != NULL)
		aux = aux->next;
	return (aux);
}

void	l_add_b(t_light **l, t_light *l_new)
{
	t_light	*aux;

	if (l)
	{
		if (*l)
		{
			aux = l_last(*l);
			aux->next = l_new;
			l_new = aux;
		}
		else
			*l = l_new;
	}
}

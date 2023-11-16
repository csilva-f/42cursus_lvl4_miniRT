/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lights_iterate.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csilva-f <csilva-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 20:44:49 by csilva-f          #+#    #+#             */
/*   Updated: 2023/11/15 23:45:24 by csilva-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT_bonus.h"

t_llst	*llst_new(t_mini *m, t_light *l)
{
	t_llst	*llst;

	llst = malloc(sizeof(t_llst));
	if (!llst)
		return (NULL);
	llst->head = 0;
	if (l)
		llst->l = l;
	llst->next = m->llst;
	return (llst);
}

t_llst	*llst_last(t_llst *l)
{
	t_llst	*aux;

	if (!l)
		return (NULL);
	aux = l;
	while (aux->next && aux->next->head != 1)
		aux = aux->next;
	return (aux);
}

void	llst_add_b(t_llst **l, t_llst *l_new)
{
	t_llst	*aux;

	if (l)
	{
		if (*l)
		{
			aux = llst_last(*l);
			aux->next = l_new;
			l_new = aux;
		}
		else
		{
			l_new->head = 1;
			*l = l_new;
		}
	}
}

void	fill_light_list(t_mini *m)
{
	t_light	*t_l;

	t_l = m->light;
	while (m->light)
	{
		llst_add_b(&m->llst, llst_new(m, m->light));
		m->light = m->light->next;
	}
	m->light = t_l;
}

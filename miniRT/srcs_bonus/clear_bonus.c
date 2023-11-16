/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csilva-f <csilva-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 19:45:42 by csilva-f          #+#    #+#             */
/*   Updated: 2023/11/15 23:59:03 by csilva-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT_bonus.h"

void	free_lights_lst(t_mini *m)
{
	t_llst	*aux_llst;

	while (m->llst->head != 1)
		m->llst = m->llst->next;
	if (m->llst->head == 1 && m->llst->next && m->llst->next->head != 1)
		m->llst = m->llst->next;
	while (m->llst->head != 1)
	{
		aux_llst = m->llst->next;
		free(m->llst);
		m->llst = aux_llst;
	}
	free(m->llst);
}

void	free_solids_lst(t_mini *m)
{
	t_solid	*aux_s;

	while (m->s->head != 1)
		m->s = m->s->next;
	if (m->s->head == 1 && m->s->next && m->s->next->head != 1)
		m->s = m->s->next;
	while (m->s->head != 1)
	{
		aux_s = m->s->next;
		free(m->s);
		m->s = aux_s;
	}
	free(m->s);
}

void	free_solids_aux(t_mini *mini)
{
	t_cone		*aux_co;
	t_cylinder	*aux_c;
	t_light		*aux_l;

	while (mini->cyl)
	{
		aux_c = mini->cyl->next;
		free(mini->cyl);
		mini->cyl = aux_c;
	}
	while (mini->co)
	{
		aux_co = mini->co->next;
		free(mini->co);
		mini->co = aux_co;
	}
	while (mini->light)
	{
		aux_l = mini->light->next;
		free(mini->light);
		mini->light = aux_l;
	}
	if (mini->llst)
		free_lights_lst(mini);
}

void	free_solids(t_mini *mini, int i)
{
	t_plane		*aux_p;
	t_sphere	*aux_s;

	while (mini->plane)
	{
		aux_p = mini->plane->next;
		free(mini->plane);
		mini->plane = aux_p;
	}
	while (mini->sp)
	{
		aux_s = mini->sp->next;
		if (mini->sp->b1 || mini->sp->b2)
		{
			while (++i < 5000)
				free(mini->sp->map[i]);
			free(mini->sp->map);
		}
		free(mini->sp);
		mini->sp = aux_s;
	}
	free_solids_aux(mini);
	if (mini->s)
		free_solids_lst(mini);
}

void	free_structs(t_mini *mini, int mlx)
{
	if (mini->is_valid && mlx)
	{
		mlx_destroy_image(mini->g->mlx, mini->g->img);
		mlx_destroy_window(mini->g->mlx, mini->g->win);
		mlx_destroy_display(mini->g->mlx);
		mlx_destroy_image(mini->g->menu_mlx, mini->g->menu_img);
		mlx_destroy_window(mini->g->menu_mlx, mini->g->menu_win);
		mlx_destroy_display(mini->g->menu_mlx);
		free(mini->g->mlx);
		free(mini->g->menu_mlx);
		free(mini->g);
	}
	free(mini->al);
	free(mini->cam);
	free_solids(mini, -1);
}

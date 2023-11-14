/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csilva-f <csilva-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 19:45:42 by csilva-f          #+#    #+#             */
/*   Updated: 2023/11/09 21:40:48 by csilva-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT_bonus.h"
#include <stdlib.h>

void	free_solids_2(t_mini *m)
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

void	free_solids_3(t_mini *mini)
{
	t_cone	*aux_co;
	t_light	*aux_l;

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
}

void	free_solids(t_mini *mini)
{
	t_plane		*aux_p;
	t_sphere	*aux_s;
	t_cylinder	*aux_c;
	int			i;

	while (mini->plane)
	{
		aux_p = mini->plane->next;
		free(mini->plane);
		mini->plane = aux_p;
	}
	while (mini->sp)
	{
		aux_s = mini->sp->next;
		i = 0;
		while (i < 5000)
		{
        	free(mini->sp->map[i]);
        	i++;
    	}
    	free(mini->sp->map);
		free(mini->sp);
		mini->sp = aux_s;
	}
	while (mini->cyl)
	{
		aux_c = mini->cyl->next;
		free(mini->cyl);
		mini->cyl = aux_c;
	}
	free_solids_3(mini);
	if (mini->s)
		free_solids_2(mini);
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
	free_solids(mini);
}

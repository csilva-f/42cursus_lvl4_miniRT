/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csilva-f <csilva-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 19:45:42 by csilva-f          #+#    #+#             */
/*   Updated: 2023/08/29 19:46:54 by csilva-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

void	free_solids(t_mini *mini)
{
	t_plane		*aux_p;
	t_sphere	*aux_s;
	t_cylinder	*aux_c;

	while (mini->plane)
	{
		aux_p = mini->plane->next;
		free(mini->plane);
		mini->plane = aux_p;
	}
	while (mini->sp)
	{
		aux_s = mini->sp->next;
		free(mini->sp);
		mini->sp = aux_s;
	}
	while (mini->cyl)
	{
		aux_c = mini->cyl->next;
		free(mini->cyl);
		mini->cyl = aux_c;
	}
}

void	free_structs(t_mini *mini, int mlx)
{
	if (mini->is_valid && mlx)
	{
		mlx_destroy_image(mini->g->mlx, mini->g->img);
		mlx_destroy_window(mini->g->mlx, mini->g->win);
		mlx_destroy_display(mini->g->mlx);
		free(mini->g->mlx);
		free(mini->g);
	}
	free(mini->al);
	free(mini->cam);
	free(mini->light);
	free_solids(mini);
}

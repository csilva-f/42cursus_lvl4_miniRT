/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solid_lst_3_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csilva-f <csilva-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 23:29:10 by csilva-f          #+#    #+#             */
/*   Updated: 2023/11/14 22:57:59 by csilva-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT_bonus.h"

void	sph_new_aux(char **vars, t_sphere **sp)
{
	if (!ft_strncmp(vars[5], "b1", ft_strlen(vars[5]) + 1))
	{
		(*sp)->b1 = 1;
		(*sp)->map = map_create_b1();
	}
	else if (!ft_strncmp(vars[5], "b2", ft_strlen(vars[5]) + 1))
	{
		(*sp)->b2 = 1;
		(*sp)->map = map_create_b2(-1);
	}
}

t_sphere	*sph_new(t_mini *m, char **vars, char ***data)
{
	t_sphere	*sp;

	sp = malloc(sizeof(t_sphere));
	if (!sp)
		return (NULL);
	sp->pos.x = float_check(m, (*data)[0]);
	sp->pos.y = float_check(m, (*data)[1]);
	sp->pos.z = float_check(m, (*data)[2]);
	sp->d = float_check(m, vars[2]) / 2;
	sp->d_squared = sp->d * sp->d;
	fill_colors(m, vars[3], &sp->color);
	sp->shine = ft_atoi(vars[4]);
	sp->b1 = 0;
	sp->b2 = 0;
	if (vars[5] != 0)
		sph_new_aux(vars, &sp);
	sp->next = NULL;
	return (sp);
}

t_sphere	*sph_last(t_sphere *sp)
{
	t_sphere	*aux;

	if (!sp)
		return (NULL);
	aux = sp;
	while (aux->next != NULL)
		aux = aux->next;
	return (aux);
}

void	sph_add_b(t_sphere **sp, t_sphere *sp_new)
{
	t_sphere	*aux;

	if (sp)
	{
		if (*sp)
		{
			aux = sph_last(*sp);
			aux->next = sp_new;
			sp_new = aux;
		}
		else
			*sp = sp_new;
	}
}

void	cy_new_aux(t_mini *m, char ***data, t_cylinder **c)
{
	(*c)->pos = coord_new(float_check(m, (*data)[0]), float_check(m, \
				(*data)[1]), float_check(m, (*data)[2]));
}

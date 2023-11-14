/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solid_lst_5_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csilva-f <csilva-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 21:56:22 by csilva-f          #+#    #+#             */
/*   Updated: 2023/11/14 22:52:44 by csilva-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT_bonus.h"

t_cone	*co_new(t_mini *m, char **vars, char ***data)
{
	t_cone	*c;

	c = malloc(sizeof(t_cone));
	co_new_aux(m, data, &c);
	ft_free_split(*data);
	*data = ft_split(vars[2], ',');
	if (count_vars(*data, 3, 4, m))
	{
		c->vec = vector_new(float_check(m, (*data)[0]), float_check(m, \
					(*data)[1]), float_check(m, (*data)[2]));
		if (fabs(c->vec.vx) > 1 || fabs(c->vec.vy) > 1 || fabs(c->vec.vz) > 1
			|| length(c->vec) != (float) 1)
			vars_errors(m, 4);
		else
		{
			c->ang = float_check(m, vars[3]) * PI / 180;
			if (c->ang < 0 || c->ang > 180)
				vars_errors(m, 4);
			else
				c->k = tan(c->ang);
			co_new_aux2(m, &c, vars);
		}
	}
	c->next = NULL;
	return (c);
}

t_cone	*co_last(t_cone *cone)
{
	t_cone	*aux;

	if (!cone)
		return (NULL);
	aux = cone;
	while (aux->next != NULL)
		aux = aux->next;
	return (aux);
}

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

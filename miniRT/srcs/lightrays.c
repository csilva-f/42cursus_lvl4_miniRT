/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lightrays.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvieira <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 16:45:27 by fvieira           #+#    #+#             */
/*   Updated: 2023/07/29 16:45:28 by fvieira          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

// p2(t) = (p.x, p.y, p.z) + (v.x, v.y, v.z) * t
// ter em conta que v e' vetor mas as contas e' como
// se fossem coordenadas penso?
t_pos	ray_pos(t_pos p, t_vector v, float t)
{
	return (coord_add(p, coord_mult_const(vector_to_pos(v), t)));
}

// vou usar a estrutura de codigo que tu criaste para os solidos na func luz 
// talvez seja temp, nao sei se se aplica bem para este caso

t_ray	*ray_new(t_mini *m, t_pos p, t_vector v)
{
	t_ray	*ray;

	ray = malloc(sizeof(t_ray));
	(void)m;
	if (!ray)
		return (NULL);
	ray->p0.x = p.x;
	ray->p0.y = p.y;
	ray->p0.z = p.z;
	ray->v1.vx = v.vx;
	ray->v1.vy = v.vy;
	ray->v1.vz = v.vz;
	ray->reflex_times = 15;
	ray->next = NULL;
	return (ray);
}

t_ray	*ray_last(t_ray *ray)
{
	t_ray	*aux;

	if (!ray)
		return (NULL);
	aux = ray;
	while (aux->next != NULL)
		aux = aux->next;
	return (aux);
}

void	ray_add_b(t_ray **ray, t_ray *ray_new)
{
	t_ray	*aux;

	if (ray)
	{
		if (*ray)
		{
			aux = ray_last(*ray);
			aux->next = ray_new;
			ray_new = aux;
		}
		else
			*ray = ray_new;
	}
}

void	ray_create(t_mini *m)
{
	int			x;
	int			y;
	float		px;
	t_pos		p;

	x = 0;
	while (x < m->g->width)
	{
		y = 0;
		px = (x + 0.5) / m->g->width;
		while (y < m->g->height)
		{
			p = pixel_pos(px, (y + 0.5) / m->g->height, m);
			ray_add_b(&m->ray, ray_new(m, p, pixel_vec(p)));
			y++;
		}
		printf(" isto esta muito lento wtf, tem de se mudar ray add b%i\n", x);
		//a funcao vai estar sempre a ir ao inicio e itera ate chegar ao ultimo
		//nao faz sentido nestecaso,so temos de fazer sempre seguido
		x++;
	}
}

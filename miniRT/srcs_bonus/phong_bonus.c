/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phong_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvieira <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 16:42:32 by fvieira           #+#    #+#             */
/*   Updated: 2023/11/26 17:49:10 by csilva-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT_bonus.h"

bool	shadow(t_mini *m, t_light *l)
{
	t_ray	*temp;
	t_pos	hit_c;

	temp = malloc(sizeof(t_ray));
	hit_c = ray_pos(m->ray->p0, m->ray->v1, m->ray->t - 0.0001);
	temp->v1 = vector_norm(vector_create(l->pos, hit_c));
	temp->sqrt_len = vector_dot(temp->v1, temp->v1);
	temp->p0 = hit_c;
	temp->t = -1;
	light_collisions(m, temp);
	if (temp->t < 0.0005 && temp->t >= 0)
		temp->t = -1;
	if (temp->t == -1 || distance(l->pos, temp->p0) \
		< distance(ray_pos(temp->p0, temp->v1, temp->t), temp->p0))
	{
		free(temp);
		return (true);
	}
	free(temp);
	return (false);
}

double	vec_cos(t_vector v1, t_vector v2)
{
	double	dot;
	double	lengths;

	dot = vector_dot(v1, v2);
	lengths = length(v1) * length(v2);
	return (dot / lengths);
}

void	phong_aux(t_mini *m, t_ray *r, t_pos **k, t_light *aux_l)
{
	double		dot;
	t_vector	l;

	(*k)[1] = multconst_rgb(aux_l->ratio, aux_l->color);
	l = vector_norm(vector_create(aux_l->pos, ray_pos(r->p0, \
					r->v1, r->t * 0.99999)));
	dot = vector_dot(r->norm_v, l);
	if (dot > 0 && shadow(m, aux_l))
	{
		(*k)[3] = multiply_rgb(multconst_rgb(dot, (*k)[1]), r->color);
		(*k)[4] = mix_rgb(multiply_rgb(multconst_rgb(0.8 * pow(vector_dot(\
			vector_norm(vector_add(vector_norm(\
			vector_mult_const(r->v1, -1)), l)), r->norm_v), r->shine), \
			(*k)[1]), r->color), aux_l->color);
	}
	else
	{
		(*k)[3] = (t_pos){0, 0, 0};
		(*k)[4] = (t_pos){0, 0, 0};
	}
}

t_pos	phong(t_mini *m, t_ray *r)
{
	t_pos		i;
	t_pos		*k;
	t_light		*aux_l;

	aux_l = m->light;
	k = malloc(5 * sizeof(t_pos));
	k[0] = multconst_rgb(m->al->ratio, m->al->color);
	i = (t_pos){0, 0, 0};
	k[2] = multiply_rgb(k[0], r->color);
	while (aux_l != NULL)
	{
		phong_aux(m, r, &k, aux_l);
		i = add_rgb(add_rgb(i, add_rgb(k[2], k[3])), k[4]);
		aux_l = aux_l->next;
	}
	free(k);
	return (i);
}

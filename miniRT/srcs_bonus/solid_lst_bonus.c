/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solid_lst_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csilva-f <csilva-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 23:17:36 by csilva-f          #+#    #+#             */
/*   Updated: 2023/11/12 13:21:42 by csilva-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT_bonus.h"

void	pl_new_aux(t_mini *m, char **vars, t_plane **pl)
{
	fill_colors(m, vars[3], &(*pl)->color);
	(*pl)->shine = ft_atoi(vars[4]);
	if (vars[5] != 0)
	{
		(*pl)->checkboard = 1;
		fill_colors(m, vars[5], &(*pl)->color2);
	}
}

t_plane	*pl_new(t_mini *m, char **vars, char ***data)
{
	t_plane	*pl;

	pl = malloc(sizeof(t_plane));
	if (!pl)
		return (NULL);
	pl->pos.x = float_check(m, (*data)[0]);
	pl->pos.y = float_check(m, (*data)[1]);
	pl->pos.z = float_check(m, (*data)[2]);
	pl->checkboard = 0;
	ft_free_split(*data);
	*data = ft_split(vars[2], ',');
	if (count_vars(*data, 3, 4, m))
	{
		pl->vec.vx = float_check(m, (*data)[0]);
		pl->vec.vy = float_check(m, (*data)[1]);
		pl->vec.vz = float_check(m, (*data)[2]);
		if (fabs(pl->vec.vx) > 1 || fabs(pl->vec.vy) > 1
			|| fabs(pl->vec.vz) > 1 || length(pl->vec) != 1)
			vars_errors(m, 4);
		else
			pl_new_aux(m, vars, &pl);
	}
	pl->next = NULL;
	pl->coef = -1 * vector_dot(pl->vec, pos_to_vector(pl->pos));
	return (pl);
}

t_plane	*pl_last(t_plane *pl)
{
	t_plane	*aux;

	if (!pl)
		return (NULL);
	aux = pl;
	while (aux->next != NULL)
		aux = aux->next;
	return (aux);
}

void	pl_add_b(t_plane **pl, t_plane *pl_new)
{
	t_plane	*aux;

	if (pl)
	{
		if (*pl)
		{
			aux = pl_last(*pl);
			aux->next = pl_new;
			pl_new = aux;
		}
		else
			*pl = pl_new;
	}
}

double fade(double t) {
    return t * t * t * (t * (t * 6 - 15) + 10);
}

double lerp(double t, double a, double b) {
    return a + t * (b - a);
}

double grad(int hash, double x) {
    int h = hash & 15;
    double grad = 1 + (h & 7); // Gradient value 1-8
    if (h & 8) grad = -grad;   // Randomly invert half of them
    return (grad * x);         // This is the key part: gradients are chosen based on hash
}

double perlin(double x, int *permutation) {
    int a = (int)floor(x) & 255;
    x -= floor(x);
    double u = fade(x);
    return lerp(u, grad(permutation[a], x), grad(permutation[a + 1], x - 1)) * 2;
}


int	**map_create(void)
{
	int	**matrix;
	int	i;
	int	j;

	srand(time(NULL));


	matrix = (int **)malloc(5000 * sizeof(int*));
	i = 0;
	int permutation[512];
    for (int z = 0; z < 512; z++) {
        permutation[z] = rand() % 255;
    }
	while (i < 5000)
	{
		j = 0;
		matrix[i] = (int *)malloc(5000 * sizeof(int));
		while (j < 5000)
		{
			double value = perlin((double)i / 5000, permutation);
			matrix[i][j] = (int)((value + 1.0) * 1000.0) + 1;
			j++;
		}

		i++;
	}
	return (matrix);
}

/*
int	**map_create(void)
{
	int	**matrix;
	int	i;
	int	j;

	matrix = (int **)malloc(5000 * sizeof(int*));
	i = 0;
	while (i < 5000)
	{
		j = 0;
		matrix[i] = (int *)malloc(5000 * sizeof(int));
		while (j < 5000)
		{
			matrix[i][j] = sin(j) * sin(i) * 1000;
			j++;
		}

		i++;
	}
	return (matrix);
}
*/
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
	sp->map = map_create();
	sp->next = NULL;
	return (sp);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solid_lst_2_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csilva-f <csilva-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 00:28:07 by csilva-f          #+#    #+#             */
/*   Updated: 2023/11/14 22:57:16 by csilva-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT_bonus.h"

double	lerp(double t, double a, double b)
{
	return (a + t * (b - a));
}

double	grad(int hash, double x)
{
	int		h;
	double	grad;

	h = hash & 15;
	grad = 1 + (h & 7); 
	if (h & 8)
		grad = -grad;
	return (grad * x);
}

double	perlin(double x, int *permutation)
{
	int		a;
	double	u;
	double	res;

	a = (int)floor(x) & 255;
	x -= floor(x);
	u = fade(x);
	res = lerp(u, grad(permutation[a], x), grad(permutation[a + 1], x - 1)) * 2;
	return (res);
}

int	**map_create_b1(void)
{
	int	**matrix;
	int	i;
	int	j;

	matrix = (int **)malloc(5000 * sizeof(int *));
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

int	**map_create_b2(int z)
{
	int		**matrix;
	int		i;
	int		j;
	int		permutation[512];
	double	value;

	srand(time(NULL));
	matrix = (int **)malloc(5000 * sizeof(int *));
	i = -1;
	while (++z < 512)
		permutation[z] = rand() % 255;
	while (++i < 5000)
	{
		j = 0;
		matrix[i] = (int *)malloc(5000 * sizeof(int));
		while (j < 5000)
		{
			value = perlin((double)i / 5000, permutation);
			matrix[i][j] = (int)((value + 1.0) * 1000.0) + 1;
			j++;
		}
	}
	return (matrix);
}

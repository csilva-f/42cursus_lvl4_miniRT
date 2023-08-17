/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csilva-f <csilva-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 14:34:00 by csilva-f          #+#    #+#             */
/*   Updated: 2023/07/11 00:54:11 by csilva-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

void	init(t_mini *mini, char **argv)
{
	mini->file = argv[1];
	mini->is_valid = 1;
	mini->al = malloc(sizeof(t_al));
	mini->cam = malloc(sizeof(t_cam));
	mini->light = malloc(sizeof(t_light));
	mini->g = malloc(sizeof(t_graphics));
	if (!mini->al || !mini->cam || !mini->light || !mini->g)
		return ;
	mini->plane = NULL;
	mini->sp = NULL;
	mini->cyl = NULL;
	mini->ray = NULL;
}

/*void	ft_s_clear(t_plane **pl, t_sphere **sp, t_cylinder **cy)
{
	t_plane		*aux_p;
	t_sphere	*aux_s;
	t_cylinder	*aux_c;

	if ((*pl) && pl)
	{
		while (*pl && pl)
		{
			aux_p = (*pl)->next;
			free(*pl);
			*pl = aux_p;
		}
	}
}*/

void	free_structs(t_mini *mini)
{
	t_plane		*aux_p;
	t_sphere	*aux_s;
	t_cylinder	*aux_c;

	if (mini->is_valid)
	{
		mlx_destroy_image(mini->g->mlx, mini->g->img);
		mlx_destroy_window(mini->g->mlx, mini->g->win);
		mlx_destroy_display(mini->g->mlx);
		free(mini->g->mlx);
	}
	free(mini->g);
	free(mini->al);
	free(mini->cam);
	free(mini->light);
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

int	count_vars(char **vars, int equal, int code, t_mini *m)
{
	int	i;

	i = 0;
	while (vars[i] != 0 && ft_strncmp(vars[i], "\0", 1))
		i++;
	if ((i == equal) || (equal == 1 && i == 2))
		return (i);
	else
	{
		vars_errors(m, code);
		return (0);
	}
}

float	float_check(t_mini *m, char *str)
{
	float	nbr;
	char	**parts;

	nbr = -1;
	parts = ft_split(str, '.');
	if (count_vars(parts, 1, 4, m) == 2)
	{
		if (ft_str_isd(parts[0]) && ft_str_isd(parts[1]))
			nbr = ft_atoi(parts[0]) + (float)ft_atoi(parts[1])
				/ powf(10, ft_strlen(parts[1]));
		else
			vars_errors(m, 4);
	}
	else if (count_vars(parts, 1, 4, m) == 1)
	{
		if (ft_str_isd(parts[0]))
			nbr = ft_atoi(parts[0]);
		else
			vars_errors(m, 4);
	}
	ft_free_split(parts);
	return (nbr);
}

int	main(int argc, char **argv)
{
	t_mini	m;

	if (argc == 2)
	{
		if (!check_file(argv[1], &m))
			return (1);
		init(&m, argv);
		get_values(&m);
		if (m.is_valid)
		{
			m.g->mlx = mlx_init();
			m.g->width = 128 * 5;
			m.g->height = 72 * 5;
			m.g->win = mlx_new_window(m.g->mlx, m.g->width,
				m.g->height, "miniRT");
			m.g->img = mlx_new_image(m.g->mlx, m.g->width, m.g->height);
			m.g->addr = mlx_get_data_addr(m.g->img, &m.g->bits_per_pixel,
				&m.g->line_length, &m.g->endian);
			raytracing(&m);
			mlx_key_hook(m.g->win, key_hook, &m);
			mlx_hook(m.g->win, 17, 1L << 17, close_game, &m);
			mlx_loop(m.g->mlx);
			//start_mlx(&m);
		}
		else
			free_structs(&m);
		if (!m.is_valid)
			return (1);
	}
	else
		return (error_handler(1, 2));
	return (0);
}

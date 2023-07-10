/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_reader.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvieira <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 18:57:04 by fvieira           #+#    #+#             */
/*   Updated: 2023/07/10 18:57:06 by fvieira          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

void	check_identifier(char *str)
{
	if (ft_strncmp(str, "A", 2) && ft_strncmp(str, "C", 2) \
			&& ft_strncmp(str, "L", 2) && ft_strncmp(str, "pl", 3) \
			&& ft_strncmp(str, "sp", 3) && ft_strncmp(str, "cy", 3))
		error_handler(1, 6);
}

void	check_line_values(t_mini *mini, char **vars)
{
	if (!ft_strncmp(vars[0], "A", 2) && count_vars(vars, 3, 5, mini))
		check_a_vars(mini, vars);
	else if (!ft_strncmp(vars[0], "C", 2) && count_vars(vars, 4, 5, mini))
		check_c_vars(mini, vars);
	else if (!ft_strncmp(vars[0], "L", 2) && count_vars(vars, 4, 5, mini))
		check_l_vars(mini, vars);
	else if (!ft_strncmp(vars[0], "pl", 3) && count_vars(vars, 4, 5, mini))
		check_pl_vars(mini, vars);
	else if (!ft_strncmp(vars[0], "sp", 3) && count_vars(vars, 4, 5, mini))
		check_sp_vars(mini, vars);
	else if (!ft_strncmp(vars[0], "cy", 3) && count_vars(vars, 6, 5, mini))
		check_cy_vars(mini, vars, NULL);
}

void	check_lines(t_mini *mini, char *aux)
{
	char	**vars;

	vars = ft_split(aux, ' ');
	check_identifier(vars[0]);
	if (!mini->is_valid)
		error_handler(mini->is_valid, 3);
	else
		check_line_values(mini, vars);
	ft_free_split(vars);
}

void	get_values(t_mini *mini)
{
	char	*aux;

	mini->fd = open(mini->file, O_RDONLY);
	while (1)
	{
		aux = get_next_line(mini->fd);
		if (aux == NULL)
			break ;
		aux = ft_remove_lb(aux);
		check_lines(mini, aux);
		free(aux);
	}
	free(aux);
	printf("A\n%f  %i\n", mini->al->ratio, mini->al->color);
	printf("C\n%f,%f,%f  %f,%f,%f %i\n", mini->cam->x, mini->cam->y, mini->cam->z, \
			mini->cam->ov_x, mini->cam->ov_y, mini->cam->ov_z, mini->cam->fov);
	printf("L\n%f,%f,%f  %f, %i\n", mini->light->x, mini->light->y, \
			mini->light->z, mini->light->ratio, mini->light->color);
	printf("pl\n%f,%f,%f %f,%f,%f  %i\n", mini->plane->x, mini->plane->y, mini->plane->z, \
			mini->plane->nv_x, mini->plane->nv_y, mini->plane->nv_z, mini->plane->color);
	printf("sp\n%f,%f,%f  %f, %i\n", mini->sp->cx, mini->sp->cy, \
			mini->sp->cz, mini->sp->d, mini->sp->color);
	printf("cyl\n%f,%f,%f %f,%f,%f  %f  %f %i\n", mini->cyl->cx, mini->cyl->cy, mini->cyl->cz, \
			mini->cyl->nv_x, mini->cyl->nv_y, mini->cyl->nv_z, mini->cyl->d, mini->cyl->h, mini->cyl->color);
}

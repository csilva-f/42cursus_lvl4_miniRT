/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_reader.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvieira <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 18:57:04 by fvieira           #+#    #+#             */
/*   Updated: 2023/09/16 15:31:52 by csilva-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

int	check_identifier(char *str)
{
	if (ft_strncmp(str, "A", 2) && ft_strncmp(str, "C", 2) \
			&& ft_strncmp(str, "L", 2) && ft_strncmp(str, "pl", 3) \
			&& ft_strncmp(str, "sp", 3) && ft_strncmp(str, "cy", 3))
	{
		error_handler(1, 6);
		return (0);
	}
	return (1);
}

void	check_line_values(t_mini *mini, char **vars)
{
	if (!ft_strncmp(vars[0], "A", 2) && count_vars(vars, 3, 5, mini))
		check_a_vars(mini, vars);
	else if (!ft_strncmp(vars[0], "C", 2) && count_vars(vars, 4, 5, mini))
		check_c_vars(mini, vars, NULL);
	else if (!ft_strncmp(vars[0], "L", 2) && count_vars(vars, 4, 5, mini))
		check_l_vars(mini, vars);
	else if (!ft_strncmp(vars[0], "pl", 3) && count_vars(vars, 4, 5, mini))
		check_pl_vars(mini, vars);
	else if (!ft_strncmp(vars[0], "sp", 3) && count_vars(vars, 4, 5, mini))
		check_sp_vars(mini, vars);
	else if (!ft_strncmp(vars[0], "cy", 3) && count_vars(vars, 6, 5, mini))
		check_cy_vars(mini, vars);
}

void	check_lines(t_mini *mini, char *aux)
{
	char	**vars;

	vars = ft_split(aux, ' ');
	mini->is_valid = check_identifier(vars[0]);
	if (!mini->is_valid)
		error_handler(mini->is_valid, 3);
	else
		check_line_values(mini, vars);
	ft_free_split(vars);
}

void	get_values(t_mini *m)
{
	char	*aux;

	m->fd = open(m->file, O_RDONLY);
	while (1)
	{
		aux = get_next_line(m->fd);
		if (aux == NULL || !m->is_valid)
			break ;
		aux = ft_remove_lb(aux);
		printf("%s\n", aux);
		check_lines(m, aux);
		free(aux);
	}
	if (m->is_valid)
		data_transform(m);
	free(aux);
	printf("A\n%f %i %i %i\n", m->al->ratio, (int)m->al->color.x, (int)m->al->color.y, (int)m->al->color.z);
	printf("C\n%f,%f", m->cam->pos.x, m->cam->pos.y);
	printf(",%f %f,%f,%f %i\n", m->cam->pos.z, \
			m->cam->vec.vx, m->cam->vec.vy, m->cam->vec.vz, m->cam->fov);
	printf("L\n%f,%f,%f %f, %i %i %i\n", m->light->pos.x, m->light->pos.y, \
			m->light->pos.z, m->light->ratio, (int)m->light->color.x, (int)m->light->color.y, (int)m->light->color.z);
	print_parser(m);
}

void	print_parser(t_mini *m)
{
	t_plane		*pl;
	t_sphere	*s;
	t_cylinder	*c;

	pl = m->plane;
	s = m->sp;
	c = m->cyl;
	while (pl != NULL)
	{
		printf("pl\n%f,%f,%f %f,%f,%f %i %i %i\n", pl->pos.x, pl->pos.y, \
				pl->pos.z, pl->vec.vx, pl->vec.vy, pl->vec.vz, (int)pl->color.x, (int)pl->color.y, (int)pl->color.z);
		pl = pl->next;
	}
	while (s != NULL)
	{
		printf("sp\n%f,%f", s->pos.x, s->pos.y);
		printf(",%f %f, %i %i %i\n", s->pos.z, s->d, (int)s->color.x, (int)s->color.y, (int)s->color.z);
		s = s->next;
	}
	while (c != NULL)
	{
		printf("cy\n%f,%f,%f %f,%f,%f %f %f %i %i %i\n", c->pos.x, c->pos.y, c->pos.z, \
				c->vec.vx, c->vec.vy, c->vec.vz, c->d, c->h, (int)c->color.x, (int)c->color.y, (int)c->color.z);
		c = c->next;
	}
}

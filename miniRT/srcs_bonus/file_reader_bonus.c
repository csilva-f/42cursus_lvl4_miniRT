/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_reader_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvieira <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 18:57:04 by fvieira           #+#    #+#             */
/*   Updated: 2023/11/11 12:20:52 by csilva-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT_bonus.h"

int	check_identifier(char *str)
{
	if (ft_strncmp(str, "A", 2) && ft_strncmp(str, "C", 2) \
			&& ft_strncmp(str, "L", 2) && ft_strncmp(str, "pl", 3) \
			&& ft_strncmp(str, "sp", 3) && ft_strncmp(str, "cy", 3) \
			&& ft_strncmp(str, "co", 3))
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
	else if (!ft_strncmp(vars[0], "co", 3) && count_vars(vars, 6, 5, mini))
		check_co_vars(mini, vars);
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
		if (aux[0] != '\n' && aux[0] != '#')
		{
			aux = ft_remove_lb(aux);
			check_lines(m, aux);
		}
		free(aux);
	}
	m->flag = true;
	if (m->is_valid)
		data_transform(m);
	free(aux);
	close(m->fd);
}

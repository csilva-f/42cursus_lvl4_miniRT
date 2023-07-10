/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csilva-f <csilva-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 14:34:00 by csilva-f          #+#    #+#             */
/*   Updated: 2023/07/09 20:03:59 by csilva-f         ###   ########.fr       */
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
	mini->plane = malloc(sizeof(t_plane));
	mini->sp = malloc(sizeof(t_sphere));
	mini->cyl = malloc(sizeof(t_cylinder));
}

void	free_structs(t_mini *mini)
{
	free(mini->al);
	free(mini->cam);
	free(mini->light);
	free(mini->plane);
	free(mini->sp);
	free(mini->cyl);
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
	t_mini	mini;

	if (argc == 2)
	{
		if (check_file(argv[1], &mini))
			return (1);
		init(&mini, argv);
		get_values(&mini);
		free_structs(&mini);
		if (!mini.is_valid)
			return (1);
	}
	else
		return (error_handler(1, 2));
	return (0);
}

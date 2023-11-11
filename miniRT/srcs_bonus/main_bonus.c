/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csilva-f <csilva-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 14:34:00 by csilva-f          #+#    #+#             */
/*   Updated: 2023/11/11 12:24:23 by csilva-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT_bonus.h"

int	count_vars(char **vars, int equal, int code, t_mini *m)
{
	int	i;

	i = 0;
	while (vars[i] != 0 && ft_strncmp(vars[i], "\0", 1))
		i++;
	if ((i == equal) || (equal == 1 && i == 2) || (!ft_strncmp(vars[0], \
					"pl", ft_strlen(vars[0]) + 1) && i == equal + 1))
		return (i);
	else
	{
		vars_errors(m, code);
		return (0);
	}
}

double	float_check(t_mini *m, char *str)
{
	double	nbr;
	char	**parts;

	nbr = -1;
	parts = ft_split(str, '.');
	if (count_vars(parts, 1, 4, m) == 2)
	{
		if (ft_str_isd(parts[0]) && ft_str_isd(parts[1]))
			nbr = ft_atoi(parts[0]) + (double)ft_atoi(parts[1])
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
		init(&m);
		get_values(&m);
		if (m.is_valid)
			init_canvas(&m);
		else
			free_structs(&m, 1);
		if (!m.is_valid)
			return (1);
	}
	else
		return (error_handler(1, 2));
	return (0);
}

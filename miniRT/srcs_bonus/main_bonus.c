/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csilva-f <csilva-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 14:34:00 by csilva-f          #+#    #+#             */
/*   Updated: 2023/09/20 21:30:51 by csilva-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT_bonus.h"

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

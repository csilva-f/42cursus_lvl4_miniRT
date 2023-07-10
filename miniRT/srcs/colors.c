/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvieira <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 19:07:43 by fvieira           #+#    #+#             */
/*   Updated: 2023/07/10 19:07:45 by fvieira          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

int	rgb_to_int(int red, int green, int blue)
{
	int		res;
	char	*str;

	printf("r: %d g: %d b: %d\n", red, green, blue);
	str = ft_rgb_to_hex(red, green, blue);
	printf("%s\n", str);
	res = ft_hex_to_int(str);
	free(str);
	printf("%d\n", res);
	return (res);
}

int	fill_colors(t_mini *m, char *str, int c)
{
	int		r;
	int		g;
	int		b;
	char	**color;

	color = ft_split(str, ',');
	if (count_vars(color, 3, 4, m))
	{
		if (ft_str_isd(color[0]) && ft_str_isd(color[1]) \
				&& ft_str_isd(color[2]))
		{
			r = ft_atoi(color[0]);
			g = ft_atoi(color[1]);
			b = ft_atoi(color[2]);
			if (r >= 0 && r <= 255 && g >= 0 && g <= 255 && b >= 0 && b <= 255)
				c = rgb_to_int(r, g, b);
			else
				vars_errors(m, 4);
		}
		else
			vars_errors(m, 4);
	}
	ft_free_split(color);
	return (c);
}

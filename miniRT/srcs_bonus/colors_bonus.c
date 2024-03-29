/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvieira <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 19:07:43 by fvieira           #+#    #+#             */
/*   Updated: 2023/11/12 13:09:13 by csilva-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT_bonus.h"

int	rgb_to_int(int red, int green, int blue)
{
	int		res;
	char	*str;

	str = ft_rgb_to_hex(red, green, blue);
	res = ft_hex_to_int(str);
	free(str);
	return (res);
}

void	fill_colors(t_mini *m, char *str, t_pos *col)
{
	char	**color;

	color = ft_split(str, ',');
	if (count_vars(color, 3, 4, m))
	{
		if (ft_str_isd(color[0]) && ft_str_isd(color[1]) \
				&& ft_str_isd(color[2]))
		{
			col->x = ft_atoi(color[0]);
			col->y = ft_atoi(color[1]);
			col->z = ft_atoi(color[2]);
			if (col->x < 0 || col->x > 255 || col->y < 0 || \
					col->y > 255 || col->z < 0 || col->z > 255)
				vars_errors(m, 4);
		}
		else
			vars_errors(m, 4);
	}
	ft_free_split(color);
}

t_pos	mix_rgb(t_pos c1, t_pos c2)
{
	c1.x *= (int)(c2.x / 255.0);
	c1.y *= (int)(c2.y / 255.0);
	c1.z *= (int)(c2.z / 255.0);
	return (c1);
}

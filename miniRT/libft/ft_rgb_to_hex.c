/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rgb_to_hex.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csilva-f <csilva-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 19:47:50 by csilva-f          #+#    #+#             */
/*   Updated: 2023/07/09 19:52:50 by csilva-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "math.h"

char	rgb_to_hex_aux(int dec)
{
	if (dec >= 0 && dec <= 9)
		return (dec + '0');
	else if (dec >= 10 && dec <= 15)
		return (dec - 10 + 'A');
	else
		return ('\0');
}

char	*ft_rgb_to_hex(int red, int green, int blue)
{
	char	*hex_s;

	hex_s = (char *)malloc(6 * sizeof(char));
	hex_s[0] = rgb_to_hex_aux(red / 16);
	hex_s[1] = rgb_to_hex_aux(red % 16);
	hex_s[2] = rgb_to_hex_aux(green / 16);
	hex_s[3] = rgb_to_hex_aux(green % 16);
	hex_s[4] = rgb_to_hex_aux(blue / 16);
	hex_s[5] = rgb_to_hex_aux(blue % 16);
	hex_s[6] = '\0';
	return (hex_s);
}

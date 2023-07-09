/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hex_to_int.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csilva-f <csilva-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 19:50:11 by csilva-f          #+#    #+#             */
/*   Updated: 2023/07/09 19:56:19 by csilva-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <math.h>

int	ft_hex_to_int(const char *hex_s)
{
	int	len;
	int	result;
	int	digit;
	int	power;
	int	i;

	i = 0;
	len = strlen(hex_s);
	result = 0;
	while (i < len)
	{
		if (hex_s[i] >= '0' && hex_s[i] <= '9')
			digit = hex_s[i] - '0';
		else if (hex_s[i] >= 'A' && hex_s[i] <= 'F')
			digit = hex_s[i] - 'A' + 10;
		else if (hex_s[i] >= 'a' && hex_s[i] <= 'f')
			digit = hex_s[i] - 'a' + 10;
		power = len - i - 1;
		result += digit * pow(16, power);
		i++;
	}
	return (result);
}

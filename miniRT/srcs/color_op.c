/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_op.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvieira <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 14:54:48 by fvieira           #+#    #+#             */
/*   Updated: 2023/09/16 16:07:29 by csilva-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"
#include <stdio.h>

t_pos	multconstRGB(float c, t_pos color)
{
	t_pos result;

	if (c > 0)
		printf("%f\n", c);
    result.x = (color.x * c);
	result.y = (color.y * c);
	result.z = (color.z * c);
	if (result.x > 255)
		result.x = 255;
	if (result.y > 255)
		result.y = 255;
	if (result.z > 255)
		result.z = 255;
	if (result.x < 0)
		result.x = 0;
	if (result.y < 0)
		result.y = 0;
	if (result.z < 0)
		result.z = 0;
    return (result);
}

t_pos	multiplyRGB(t_pos color1, t_pos color2)
{
	t_pos result;
    result.x = (int)((color1.x * color2.x) / 255.0);
    result.y = (int)((color1.y * color2.y) / 255.0);
    result.z = (int)((color1.z * color2.z) / 255.0);
    return (result);
}

t_pos	addRGB(t_pos color1, t_pos color2)
{
	t_pos result;

    result.x = (color1.x + color2.x);
	if (result.x > 255)
		result.x = 255;
    result.y = (color1.y + color2.y);
	if (result.y > 255)
		result.y = 255;
	result.z = (color1.z + color2.z);
	if (result.z > 255)
		result.z = 255;
    return (result);
}

t_pos	subRGB(t_pos color1, t_pos color2)
{
	t_pos result;

    result.x = (color1.x + color2.x);
	if (result.x < 0)
		result.x = 0;
    result.y = (color1.y + color2.y);
	if (result.y < 0)
		result.y = 0;
	result.z = (color1.z + color2.z);
	if (result.z < 0)
		result.z = 0;
    return (result);
}

t_pos	divideRGB(t_pos color1, t_pos color2)
{
   	t_pos result;

   	if (color2.x == 0 || color2.y == 0 || color2.z == 0)
   		return (color1);
    result.x = (int)((color1.x * 255.0 / color2.x));
    result.y = (int)((color1.y * 255.0 / color2.y));
    result.z = (int)((color1.z * 255.0 / color2.z));
    return (result);
}

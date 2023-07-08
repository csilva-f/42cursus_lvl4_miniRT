/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csilva-f <csilva-f@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 20:19:36 by csilva-f          #+#    #+#             */
/*   Updated: 2022/11/06 10:32:55 by csilva-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	ft_isalnum(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') \
			|| (c >= '0' && c <= '9'))
		return (1);
	return (0);
}

/*int	main(void)
{
	int	c = '1';

	printf("%d", ft_isalnum(c));
	return (0);
}*/

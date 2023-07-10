/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csilva-f <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 20:22:17 by csilva-f          #+#    #+#             */
/*   Updated: 2023/07/11 00:49:27 by csilva-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (!s1 || !s2)
		return (0);
	while (s1[i] == s2[i] && s1[i] != '\0')
		i++;
	if (i >= n)
		return (0);
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

/*int	main(void)
{
	char	s1[] = "{[123$a";
	char	s2[] = "{[124";

	int x = ft_strncmp(s1, s2, 4);
	printf("strncmp(str1, str2) = %d\n", x);
	return (0);
}*/

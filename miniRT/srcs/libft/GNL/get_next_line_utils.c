/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csilva-f <csilva-f@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 20:56:08 by csilva-f          #+#    #+#             */
/*   Updated: 2022/11/17 22:01:23 by csilva-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strl(const char *str)
{
	size_t	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] != '\0')
		i++;
	return (i);
}

char	*ft_strc(const char *s, int c)
{
	size_t	i;
	size_t	len;
	char	*str;

	i = -1;
	if (!s)
		return (NULL);
	len = ft_strl(s);
	str = (char *)s;
	while (str[++i] != '\0')
	{
		if (str[i] == c)
			return (&str[i]);
	}
	if (c == '\0')
		return (&str[len]);
	return (0);
}

char	*ft_strjn(char *s1, char *s2)
{
	size_t		size;
	char		*str;
	size_t		i;
	size_t		j;

	if (s1 == NULL)
	{
		s1 = (char *)malloc(1 * sizeof(char));
		s1[0] = '\0';
	}
	if (s1 == NULL || s2 == NULL)
		return (NULL);
	size = ft_strl((char *)s1) + ft_strl((char *)s2) + 1;
	str = (char *)malloc(size * sizeof(char));
	if (str == NULL)
		return (NULL);
	i = -1;
	while (s1[++i] != '\0')
		str[i] = s1[i];
	j = -1;
	while (s2[++j] != '\0')
		str[i + j] = s2[j];
	str[i + j] = '\0';
	free(s1);
	return (str);
}

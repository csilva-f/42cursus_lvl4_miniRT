/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_remove_lb.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csilva-f <csilva-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 19:29:45 by csilva-f          #+#    #+#             */
/*   Updated: 2023/07/08 19:30:16 by csilva-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_remove_lb(char *str)
{
	char	*new_s;
	int		len;
	int		i;

	i = -1;
	len = ft_strlen(str);
	if (str[len - 1] == '\n')
	{
		new_s = malloc(sizeof(char) * len);
		while (str[++i] != '\n')
			new_s[i] = str[i];
		new_s[i] = '\0';
		free(str);
		str = ft_strdup(new_s);
		free(new_s);
	}
	return (str);
}

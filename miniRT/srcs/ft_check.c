/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csilva-f <csilva-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 14:57:52 by csilva-f          #+#    #+#             */
/*   Updated: 2023/07/08 15:31:48 by csilva-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

int	error_handler(int code)
{
	printf("Error(%d): ", code);
	if (code == 1)
		printf("the file is not of type .rt");
	else if (code == 2)
		printf("wrong number of arguments");
	printf("\n");
	return (1);
}

int	check_file(char *file_name)
{
	int	i;
	int	c;

	i = ft_strlen(file_name) - 1;
	c = -1;
	while (i > 0 && file_name[i] != '.')
		i--;
	if (file_name[i] == '.')
	{
		i++;
		c = ft_strncmp(&file_name[i], "rt", 2);
	}
	if (!c)
		return (error_handler(1));
	return (0);
}
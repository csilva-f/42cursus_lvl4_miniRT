/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csilva-f <csilva-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 14:57:52 by csilva-f          #+#    #+#             */
/*   Updated: 2023/07/08 19:17:59 by csilva-f         ###   ########.fr       */
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
	else if (code == 3)
		printf("a non empty line doesn't start with an identifier");
	else if (code == 4)
		printf("1 or more numbers provided is not valid");
	else if (code == 5)
		printf("i or more lines with a wrong number of arguments");
	printf("\n");
	return (1);
}

int	check_file(char *file_name, t_mini *mini)
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
	{
		mini->file = file_name;
		return (0);
	}
	return (error_handler(1));
}

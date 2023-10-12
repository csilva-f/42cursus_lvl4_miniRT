/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csilva-f <csilva-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 14:57:52 by csilva-f          #+#    #+#             */
/*   Updated: 2023/07/08 19:17:59 by csilva-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT_bonus.h"

bool	error_handler(int is_valid, int code)
{
	if (is_valid)
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
			printf("1 or more lines with a wrong number of arguments");
		else if (code == 6)
			printf("invalid letter");
		else if (code == 7)
			printf("invalid repeated letter");
		printf("\n");
	}
	return (false);
}

void	vars_errors(t_mini *mini, int code)
{
	error_handler(mini->is_valid, code);
	mini->is_valid = 0;
}

bool	check_file(char *file_name, t_mini *mini)
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
		return (true);
	}
	mini->is_valid = 0;
	return (error_handler(1, 1));
}

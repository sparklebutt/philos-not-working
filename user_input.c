/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araveala <araveala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 10:22:30 by araveala          #+#    #+#             */
/*   Updated: 2024/07/17 12:52:32 by araveala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	argument_count(int	argc)
{
	if (argc < 5 || argc > 6)
	{
		printf("argument count is incorrect\n");
		return (1);
	}
	return (0);
}

/*		if (argv[i] == NULL)
		{
			printf("syntax error: argv[%d] is null\n", i);
			return (0);
			}*/

int string_valid(char **argv)
{
	int	i;
	int	x;

	i = 0;
	x = 0;
	while (++i && argv[i])
	{
		while (argv[i][x]) 
		{
			if (ft_isdigit(argv[i][x]) == 0)
			{
				printf("syntax error: only (+) numbers are valid input\n");
				return (1);
			}
			x++;
		}
		x = 0;
	}
	return (0); //success
}

int	check_input(int argc, char **argv)
{
	if (argument_count(argc) == 1)
	{
		return (1);
	}
	if (string_valid(argv) == 1)
	{
		return (1);
	}
	else
		return (0);
}

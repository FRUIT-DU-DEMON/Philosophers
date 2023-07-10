/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlabouit <hlabouit@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 20:59:40 by hlabouit          #+#    #+#             */
/*   Updated: 2023/07/09 18:55:34 by hlabouit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../philo.h"

int	long_negative_nb_error(char **av)
{
	char	**output;
	long	data;
	int		i;

	i = 0;
	output = split_input(av);
	while (output[i])
	{
		data = ft_atoi(output[i]);
		if (data > 2147483647 || data <= 0)
		{
			printf("Error\ninput must be a strictly positive integers\n");
			free_memory(output);
			return (1);
		}
		i++;
	}
	free_memory(output);
	return (0);
}

int	not_integer_error(char **av)
{
	char	**output;
	int		i;
	int		j;

	i = 0;
	output = split_input(av);
	while (output[i])
	{
		j = 0;
		if (output[i][j] == '+')
			j++;
		while (output[i][j])
		{
			if (ft_isdigit(output[i][j]) == 0)
			{
				printf("Error\ninput must be a strictly positive integers\n");
				free_memory(output);
				return (1);
			}
			j++;
		}
		i++;
	}
	free_memory(output);
	return (0);
}

int check_input_errors(char **av)
{
	if (long_negative_nb_error(av) == 1)
		return (1);
	else if (not_integer_error(av) == 1)
		return (1);
	return (0);
}
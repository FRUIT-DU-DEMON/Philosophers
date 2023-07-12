/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlabouit <hlabouit@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 20:45:30 by hlabouit          #+#    #+#             */
/*   Updated: 2023/07/11 23:59:47 by hlabouit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../philo.h"

int	len_of_input(char **av)
{
	int	i;
	int	j;
	int	len;

	i = 1;
	len = 0;
	while (av[i])
	{
		j = 0;
		while (av[i][j])
		{
			j++;
			len++;
		}
		i++;
	}
	return (len + i - 1);
}

char	*join_input(char **av)
{
	char	*output;
	int		len;
	int		i;
	int		j;
	int		k;

	i = 0;
	k = 0;
	len = len_of_input(av);
	output = malloc((len + 1) * sizeof(char));
	if (output == NULL)
		return (NULL);
	while (av[++i])
	{
		j = -1;
		while (av[i][++j])
			output[k++] = av[i][j];
		output[k++] = ' ';
	}
	output[k] = '\0';
	return (output);
}

char	**split_input(char **av)
{
	char	*input;
	char	**output;

	input = join_input(av);
	output = ft_split(input, ' ');
	free(input);
	return (output);
}

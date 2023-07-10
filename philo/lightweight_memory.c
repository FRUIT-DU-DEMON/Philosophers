/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lightweight_memory.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlabouit <hlabouit@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 17:27:09 by hlabouit          #+#    #+#             */
/*   Updated: 2023/07/01 19:18:49 by hlabouit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"philo.h"

void	free_memory(char **output)
{
	int	i;

	i = 0;
	while (output[i])
	{
		free(output[i]);
		i++;
	}
	free(output);
}
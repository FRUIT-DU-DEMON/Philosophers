/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlabouit <hlabouit@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 01:23:48 by hlabouit          #+#    #+#             */
/*   Updated: 2023/07/12 01:49:23 by hlabouit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"philo.h"

int	main(int ac, char **av)
{
	t_philo_data	*table;

	if (ac < 5 || ac > 6)
	{
		printf("Error\ninvalid number of arguments\n");
		return (1);
	}
	if (check_input_errors(av) == 1)
		return (1);
	table = initialize_data(av);
	if (!table)
		return (1);
	if (threading_philos(table) == 1)
		return (1);
	check_philo_state(table);
	return (0);
}

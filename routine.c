/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlabouit <hlabouit@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/02 01:37:59 by hlabouit          #+#    #+#             */
/*   Updated: 2023/07/02 18:04:49 by hlabouit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"philo.h"

t_philos_data initialize_data(char **av)
{
	t_philos_data philo;

	philo.s_number = ft_atoi(av[1]);
	philo.t_while_wating = ft_atoi(av[2]);
	philo.t_while_eating = ft_atoi(av[3]);
	philo.t_while_sleeping = ft_atoi(av[4]);
	philo.meals = ft_atoi(av[5]);
	return (philo);
}

void	routine(void *ptr)
{
	
}

void	threading_philos(t_philos_data philo)
{
	pthread_t *threads;
	
	int i = 0;
	philo = initialize_data(philo.av);
	threads = malloc(ft_atoi(philo.s_number) * sizeof(pthread_t));
	while (philo.s_number)
	{
		
	}
	
}

int main(int ac, char **av)
{
	if (ac < 5 || ac > 6)
	{
		printf("Error\ninvalid number of arguments\n");
		return (1);
	}
	if (check_input_errors(av) == 1)
		return (1);
}






// // initialize data into parsing functions;
// /*allocate an array which is the table of philos of type struct that countains the philos data each case 
// will be passed as an argument to the routine function*/
// //allocate the threads
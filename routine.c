/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlabouit <hlabouit@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/02 01:37:59 by hlabouit          #+#    #+#             */
/*   Updated: 2023/07/03 02:51:44 by hlabouit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"philo.h"

t_philos_data *initialize_data(char **av)
{
	int i;
	int id;
	int ph_nb;
	t_philos_data *table;

	i = 0;
	id = 1;
	ph_nb = ft_atoi(av[1]);
	table = malloc(ph_nb * sizeof(t_philos_data));
	while(ph_nb)
	{
		table[i].ph_nb = ph_nb;
		table[i].t_while_wating = ft_atoi(av[2]);
		table[i].t_while_eating = ft_atoi(av[3]);
		table[i].t_while_sleeping = ft_atoi(av[4]);
		table[i].ph_id = id;
		i++;
		id++;
		ph_nb--;
	}
	return(table);
}

void	*routine(void *ptr)
{
	t_philos_data philo;

	philo = *(t_philos_data *)ptr; 
	while(1)
	{
		printf("%d has taken a fork\n", philo.ph_id);
		printf("%d is eating\n", philo.ph_id);
		printf("%d is sleeping\n", philo.ph_id);
		printf("%d is thinking\n", philo.ph_id);
	}
	return (ptr);
}

int	threading_philos(t_philos_data *table, char **av)
{
	int i;
	int ph_nb;

	i = 0;
	ph_nb = ft_atoi(av[1]);
	table = malloc(ph_nb * sizeof(t_philos_data));
	while(ph_nb)
	{
		if (pthread_create(&table[i].philo, NULL, &routine, &table[i]) != 0)
		{
			printf("Error\npthread_create function has failed\n");
			return (1);
		}
		// if (pthread_detach(table[i].philo) != 0)
		// {
		// 	printf("Error\npthread_detach function has failed\n");
		// 	return (1);
		// }
		i++;
		ph_nb--;
	}
	i = 0;
	ph_nb = ft_atoi(av[1]);
	while(ph_nb)
	{
		if (pthread_detach(table[i].philo) != 0)
		{
			printf("Error\npthread_detach function has failed\n");
			return (1);
		}
		i++;
		ph_nb--;
	}
	return (0);
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
	t_philos_data *table;

	table = initialize_data(av);
	threading_philos(table, av);
}






// // initialize data into parsing functions;
// /*allocate an array which is the table of philos of type struct that countains the philos data each case 
// will be passed as an argument to the routine function*/
// //allocate the threads
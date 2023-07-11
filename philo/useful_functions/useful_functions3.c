/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   useful_functions3.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlabouit <hlabouit@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/02 19:59:51 by hlabouit          #+#    #+#             */
/*   Updated: 2023/07/11 21:20:51 by hlabouit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../philo.h"

t_philo_data	*initialize_data(char **av)
{
	t_philo_data	*table;
	int				i;
	int				ph_nb;

	i = 0;
	ph_nb = ft_atoi(av[1]);
	table = malloc(ph_nb * sizeof(t_philo_data));
	if (!table)
		return (NULL);
	while (i < ph_nb)
	{
		table[i].ph_id = i + 1;
		table[i].ph_nb = ph_nb;
		table[i].t_to_die = ft_atoi(av[2]);
		table[i].t_to_eat = ft_atoi(av[3]);
		table[i].t_to_sleep = ft_atoi(av[4]);
		if (av[5])
			table[i].total_meals = ft_atoi(av[5]);
		else
			table[i].total_meals = -1;
		table[i].meals_eaten = 0;
		table[i].last_meal_time = get_current_time();
		table[i].start_time = get_current_time();
		i++;
	}
	return (table);
}

int	initialize_mutexes(t_philo_data *table)
{
	int i;
	pthread_mutex_t *routine_dispaly;

	i = 0;
	routine_dispaly = malloc(sizeof(pthread_mutex_t));
	if (!routine_dispaly)
		return -1;
	pthread_mutex_init(routine_dispaly, NULL);
	while(i < table->ph_nb)
	{
		table[i].routine_dispaly = routine_dispaly;
		if (pthread_mutex_init(&table[i].last_meal_time_update, NULL) != 0)
			return (-1);
		if (pthread_mutex_init(&table[i].meals_eaten_update, NULL) != 0)
			return (-1);
		if (pthread_mutex_init(&table[i].fork, NULL) != 0)
			return (-1);
		i++;
	}
	return (0);
}


long long	get_current_time(void)
{
	struct timeval	tv;
	long long		current_time;
	
	gettimeofday(&tv, NULL);
	current_time = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	return(current_time);
}

void	customized_usleep(int sleep_duration)
{
	long long	current_time;

	current_time = get_current_time();
	while (get_current_time() - current_time < sleep_duration)
		usleep(sleep_duration);
}

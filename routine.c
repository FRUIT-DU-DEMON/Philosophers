/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlabouit <hlabouit@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/02 01:37:59 by hlabouit          #+#    #+#             */
/*   Updated: 2023/07/04 23:01:12 by hlabouit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"philo.h"

t_philo_data *initialize_data(char **av)
{
	int i;
	int id;
	int ph_nb;
	t_philo_data *philo;

	i = 0;
	id = 1;
	ph_nb = ft_atoi(av[1]);
	philo = malloc(ph_nb * sizeof(t_philo_data));
	while(i < ph_nb)
	{
		philo[i].ph_id = id;
		philo[i].ph_nb = ph_nb;
		philo[i].t_to_die = ft_atoi(av[2]);
		philo[i].t_while_eating = ft_atoi(av[3]);
		philo[i].t_while_sleeping = ft_atoi(av[4]);
		if (av[5])
			philo[i].total_meals = ft_atoi(av[5]);
		else
			philo[i].total_meals = -1;
		philo[i].meals_eaten = 0;
		philo[i].last_meal_time = get_current_time();
		philo[i].start_time = get_current_time();
		i++;
		id++;
	}
	return(philo);
}

long long get_current_time(void)
{
	struct timeval tv;
	long long current_time;
	
	gettimeofday(&tv, NULL);
	current_time = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	return(current_time);
}

void customized_usleep(int sleep_duration)
{
	long long current_time;

	current_time = get_current_time();
	while (get_current_time() - current_time < sleep_duration)
    	usleep(sleep_duration);
}

void	*routine(void *ptr)
{
	t_philo_data *philo;

	philo = (t_philo_data *)ptr;
	if (philo->ph_id % 2 != 0)
		customized_usleep(philo->t_while_eating);
	while(1)
	{
		pthread_mutex_lock(&philo->fork);
		printf("\n timestamp = %lld id = %d has taken a fork\n", (get_current_time() - philo->start_time), philo->ph_id);
		printf("\n timestamp = %lld id = %d eating\n", (get_current_time() - philo->start_time), philo->ph_id);
		customized_usleep(philo->t_while_eating);
		philo->meals_eaten++;
		philo->last_meal_time = get_current_time();
		printf("\n timestamp = %lld id = %d sleeping\n", (get_current_time() - philo->start_time), philo->ph_id);
		customized_usleep(philo->t_while_sleeping);
		printf("\n timestamp = %lld id = %d thinking\n", (get_current_time() - philo->start_time), philo->ph_id);
		pthread_mutex_unlock(&philo->fork);
	}
	return (ptr);
}

int	threading_philos(t_philo_data *table)
{
	int i;

	i = 0;
	while(i < table->ph_nb)
	{
		pthread_mutex_init(&table[i].fork, NULL);
		if (pthread_create(&table[i].philo, NULL, &routine, &table[i]) != 0)
		{
			printf("Error\npthread_create function has failed\n");
			return (1);
		}
		i++;
	}
	i = 0;
	while(i < table->ph_nb)
	{
		pthread_mutex_destroy(&table[i].fork);
		if (pthread_detach(table[i].philo) != 0)
		{
			printf("Error\npthread_detach function has failed\n");
			return (1);
		}
		i++;
	}
	return (0);
}

int	check_philo_death(t_philo_data *table)
{
	int i;

	while (1)
	{
		i = 0;
		while (i < table->ph_nb)
		{
			if (get_current_time() - table[i].last_meal_time > table->t_to_die)
			{
				printf("\n timestamp = %lld id = %d died\n", (get_current_time() - table[i].start_time), table[i].ph_id);
				return (0);
			}
			if (table->total_meals != -1 && table[i].meals_eaten == table->total_meals)//increment a variable to check if it is equal to ph_nb
			i++;
		}
	}
	return (1);
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
	t_philo_data *table;

	table = initialize_data(av);
	threading_philos(table);
	if (check_philo_death(table) == 0)
		return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlabouit <hlabouit@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/02 01:37:59 by hlabouit          #+#    #+#             */
/*   Updated: 2023/07/11 21:16:16 by hlabouit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"philo.h"

void	eating_process(t_philo_data	*philo)
{
	pthread_mutex_lock(&philo->fork);
	pthread_mutex_lock(philo->routine_dispaly);
	printf("%lld %d has taken a fork\n", (get_current_time() - philo->start_time), philo->ph_id);
	pthread_mutex_unlock(philo->routine_dispaly);
	pthread_mutex_lock(philo->next_fork);
	pthread_mutex_lock(philo->routine_dispaly);
	printf("%lld %d has taken a fork\n", (get_current_time() - philo->start_time), philo->ph_id);
	pthread_mutex_unlock(philo->routine_dispaly);
	customized_usleep(philo->t_to_eat);
	pthread_mutex_lock(&philo->last_meal_time_update);
	philo->last_meal_time = get_current_time();
	pthread_mutex_unlock(&philo->last_meal_time_update);
	pthread_mutex_lock(&philo->meals_eaten_update);
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->meals_eaten_update);
	pthread_mutex_unlock(philo->next_fork);
	pthread_mutex_unlock(&philo->fork);
	pthread_mutex_lock(philo->routine_dispaly);
	printf("%lld %d is eating\n", (get_current_time() - philo->start_time), philo->ph_id);
	pthread_mutex_unlock(philo->routine_dispaly);
}


void	*routine(void *ptr)
{
	t_philo_data	*philo;

	philo = (t_philo_data *)ptr;
	if (philo->ph_id % 2 != 0)
		usleep(100);
	while (1)
	{
		eating_process(philo);
		pthread_mutex_lock(philo->routine_dispaly);
		printf("%lld %d is sleeping\n", (get_current_time() - philo->start_time), philo->ph_id);
		pthread_mutex_unlock(philo->routine_dispaly);
		customized_usleep(philo->t_to_sleep);
		pthread_mutex_lock(philo->routine_dispaly);
		printf("%lld %d is thinking\n", (get_current_time() - philo->start_time), philo->ph_id);
		pthread_mutex_unlock(philo->routine_dispaly);
	}
	return (ptr);
}


int	threading_philos(t_philo_data *table)
{
	int i;

	i = 0;
	if (initialize_mutexes(table) == -1)
		return(1);
	while (i < table->ph_nb)
	{
		if (table[i].ph_id == table->ph_nb)
		{
			table[i].next_fork = &table[0].fork;
			break;
		}
		table[i].next_fork = &table[i + 1].fork;
		i++;
	}
	i = 0;
	while (i < table->ph_nb)
	{
		if (pthread_create(&table[i].philo, NULL, &routine, &table[i]) != 0)
		{
			printf("Error\npthread_create function has failed\n");
			return (1);
		}
		if (pthread_detach(table[i].philo) != 0)
		{
			printf("Error\npthread_detach function has failed\n");
			return (1);
		}
		i++;
	}
	return (0);
}

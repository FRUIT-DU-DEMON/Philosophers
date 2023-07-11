/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlabouit <hlabouit@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/02 01:37:59 by hlabouit          #+#    #+#             */
/*   Updated: 2023/07/11 19:02:45 by hlabouit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"philo.h"

t_philo_data	*initialize_data(char **av)
{
	t_philo_data	*philo;
	int				i;
	int				ph_nb;

	i = 0;
	ph_nb = ft_atoi(av[1]);
	philo = malloc(ph_nb * sizeof(t_philo_data));
	while (i < ph_nb)
	{
		philo[i].ph_id = i + 1;
		philo[i].ph_nb = ph_nb;
		philo[i].t_to_die = ft_atoi(av[2]);
		philo[i].t_to_eat = ft_atoi(av[3]);
		philo[i].t_to_sleep = ft_atoi(av[4]);
		if (av[5])
			philo[i].total_meals = ft_atoi(av[5]);
		else
			philo[i].total_meals = -1;
		philo[i].meals_eaten = 0;
		philo[i].last_meal_time = get_current_time();
		philo[i].start_time = get_current_time();
		i++;
	}
	return (philo);
}

void	*routine(void *ptr)
{
	t_philo_data	*philo;

	philo = (t_philo_data *)ptr;
	if (philo->ph_id % 2 != 0)
		usleep(100);
	while (1)
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
		// up eting
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

void	initialize_mutexes(t_philo_data *table)
{
	int i;
	pthread_mutex_t *routine_dispaly;

	i = 0;
	routine_dispaly = malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(routine_dispaly, NULL);
	while(i < table->ph_nb)
	{
		table[i].routine_dispaly = routine_dispaly;
		pthread_mutex_init(&table[i].last_meal_time_update, NULL);
		pthread_mutex_init(&table[i].meals_eaten_update, NULL);
		pthread_mutex_init(&table[i].fork, NULL);
		i++;
	}
}

int	threading_philos(t_philo_data *table)
{
	int i;

	i = 0;
	initialize_mutexes(table);
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

int	check_philo_total_meals(t_philo_data *table)
{
	int	i;
	int	flag;

	flag = 0;
	i = 0;
	while (i < table->ph_nb)
	{
		usleep(100);
		pthread_mutex_lock(&table[i].meals_eaten_update);
		if (table[i].meals_eaten == table->total_meals)
		{
			flag++;
			if (flag == table->ph_nb)
			{
				pthread_mutex_lock(table[i].routine_dispaly);
				return(table->total_meals);
			}
		}
		pthread_mutex_unlock(&table[i].meals_eaten_update);
		i++;
	}
	return (-1);
}

int	check_philo_death(t_philo_data *table)
{
	int	i;
	int	flag;

	flag = 0;
	while (1)
	{
		i = 0;
		while (i < table->ph_nb)
		{
			usleep(100);
			pthread_mutex_lock(&table[i].last_meal_time_update);
			if (get_current_time() - table[i].last_meal_time >= table->t_to_die)
			{
				pthread_mutex_lock(table[i].routine_dispaly);
				printf("%lld %d died\n", (get_current_time() - table[i].start_time), table[i].ph_id);
				return (0);
			}
			pthread_mutex_unlock(&table[i].last_meal_time_update);
			if (check_philo_total_meals(table) != -1)
				return table->total_meals;
			i++;
		}
	}
	return (1);
}

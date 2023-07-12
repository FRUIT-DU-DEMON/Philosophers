/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_philo_state.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlabouit <hlabouit@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 21:15:41 by hlabouit          #+#    #+#             */
/*   Updated: 2023/07/12 01:13:30 by hlabouit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"philo.h"

int	check_philo_total_meals(t_philo_data *table)
{
	int	i;
	int	flag;

	flag = 0;
	i = 0;
	while (i < table->ph_nb)
	{
		usleep(300);
		pthread_mutex_lock(&table[i].meals_eaten_update);
		if (table[i].meals_eaten == table->total_meals)
		{
			flag++;
			if (flag == table->ph_nb)
			{
				pthread_mutex_lock(table[i].routine_dispaly);
				return (table->total_meals);
			}
		}
		pthread_mutex_unlock(&table[i].meals_eaten_update);
		i++;
	}
	return (-1);
}

void	check_philo_state(t_philo_data *table)
{
	int	i;
	int	flag;

	flag = 0;
	while (1)
	{
		i = 0;
		while (i < table->ph_nb)
		{
			usleep(300);
			pthread_mutex_lock(&table[i].last_meal_time_update);
			if (get_current_time() - table[i].last_meal_time >= table->t_to_die)
			{
				pthread_mutex_lock(table[i].routine_dispaly);
				printf("%lld %d died\n",
					(get_current_time() - table[i].start_time), table[i].ph_id);
				return ;
			}
			pthread_mutex_unlock(&table[i].last_meal_time_update);
			if (check_philo_total_meals(table) != -1)
				return ;
			i++;
		}
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   useful_functions3.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlabouit <hlabouit@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/02 19:59:51 by hlabouit          #+#    #+#             */
/*   Updated: 2023/07/11 18:52:31 by hlabouit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../philo.h"

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

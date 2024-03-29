/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlabouit <hlabouit@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 20:46:13 by hlabouit          #+#    #+#             */
/*   Updated: 2023/07/12 01:43:04 by hlabouit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include<stdio.h>
# include<stdlib.h>
# include<unistd.h>
# include<pthread.h>
# include<sys/time.h>

typedef struct t_philo_data
{
	pthread_t		philo;
	pthread_mutex_t	fork;
	pthread_mutex_t	*next_fork;
	pthread_mutex_t	*routine_dispaly;
	pthread_mutex_t	last_meal_time_update;
	pthread_mutex_t	meals_eaten_update;
	int				ph_id;
	int				ph_nb;
	int				t_to_die;
	int				t_to_eat;
	int				t_to_sleep;
	int				total_meals;
	int				meals_eaten;
	long long		last_meal_time;
	long long		start_time;
}	t_philo_data;

int				len_of_input(char **av);
char			*join_input(char **av);
char			**split_input(char **av);
char			**ft_split(char *s, char c);
char			*ft_strncpy(char *s1, char *s2, int n);
int				ft_isdigit(int c);
int				ft_strlen(char *s);
long			ft_atoi(char *str);
int				long_negative_nb_error(char **av);
int				not_integer_error(char **av);
int				check_input_errors(char **av);
t_philo_data	*initialize_data(char **av);
long long		get_current_time(void);
void			customized_usleep(int sleep_duration);
void			eating_process(t_philo_data	*philo);
void			*routine(void *ptr);
int				threading_philos(t_philo_data *table);
int				initialize_mutexes(t_philo_data *table);
void			initialize_forks(t_philo_data *table);
int				check_philo_total_meals(t_philo_data *table);
void			check_philo_state(t_philo_data *table);
void			free_memory(char **output);

#endif
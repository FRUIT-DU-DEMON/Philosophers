/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlabouit <hlabouit@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 20:46:13 by hlabouit          #+#    #+#             */
/*   Updated: 2023/07/04 19:01:32 by hlabouit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
#define PHILO_H

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
#include<sys/time.h>

typedef struct t_philo_data
{
    pthread_t philo;
    pthread_mutex_t fork;
    int ph_nb;
    int t_while_wating;
    int t_while_eating;
    int t_while_sleeping;
    int total_meals;
    int ph_id;
    long long start_time;
} t_philo_data;


int     len_of_input(char **av);
char    *join_input(char **av);
char    **split_input(char **av);
char	**ft_split(char *s, char c);
char	*ft_strncpy(char *s1, char *s2, int n);
int     ft_isdigit(int c);
int	    ft_strlen(char *s);
int     ft_atoi(char *str);
int     long_negative_nb_error(char **av);
int     not_integer_error(char **av);
int     check_input_errors(char **av);





long long get_current_time(void);




 




void	free_memory(char **output);

#endif
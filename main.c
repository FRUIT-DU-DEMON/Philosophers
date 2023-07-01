/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlabouit <hlabouit@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 23:27:54 by hlabouit          #+#    #+#             */
/*   Updated: 2023/06/30 19:40:47 by hlabouit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
//(id + 1) % num_of_philos
int shared_data = 0;
pthread_mutex_t mutex;

void *rtn()
{
    int i = 0;
    while (i < 1000000)
    {
        pthread_mutex_lock(&mutex);
        shared_data++;
        pthread_mutex_unlock(&mutex);
        i++;
    }
    return NULL;
}

int main(int ac, char **av)
{
    pthread_t thread1;
    pthread_t thread2;
    pthread_t thread3;
    pthread_t thread4;
    pthread_mutex_init(&mutex, NULL);
    pthread_create(&thread1, NULL, &rtn, NULL);
    pthread_create(&thread2, NULL, &rtn, NULL);
    pthread_create(&thread3, NULL, &rtn, NULL);
    pthread_create(&thread4, NULL, &rtn, NULL);
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    pthread_join(thread3, NULL);
    pthread_join(thread4, NULL);
    pthread_mutex_destroy(&mutex);
    printf("%d\n", shared_data);
}


















//mutexes
//parsig : handling negative and 0
// create list which contains : philos' data---> (index of philos
                                                //time to die /eat /sleep
                                                //number of meals /philos)
//code my own usleep and my own get_timeof_day

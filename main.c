/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlabouit <hlabouit@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 23:27:54 by hlabouit          #+#    #+#             */
/*   Updated: 2023/06/25 18:10:55 by hlabouit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>

void *rtn()
{
    printf("testing threads\n");
    sleep(4);
    printf("END\n");
    
}

int main(int ac, char **av)
{
    pthread_t thread1;
    pthread_t thread2;
    if (pthread_create(&thread1, NULL, &rtn, NULL) != 0)
        return 1;
    if (pthread_create(&thread2, NULL, &rtn, NULL) != 0)
        return 2;
    if (pthread_join(thread1, NULL) != 0)
        return 3;
    if (pthread_join(thread2, NULL) != 0)
        return 4;
    return 0;
}
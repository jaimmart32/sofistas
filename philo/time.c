/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaimmart <jaimmart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 12:41:54 by jaimmart          #+#    #+#             */
/*   Updated: 2023/09/28 15:13:51 by jaimmart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*Sleeps the miliseconds passed as parameter.*/
void	ft_msleep(long time_in_ms)
{
	long	u_sec;

	u_sec = time_in_ms * 1000;
	usleep(u_sec);
}

/*Returns current time in miliseconds.*/
long	current_time(void)
{
	struct timeval	current_time;

	if (gettimeofday(&current_time, NULL))
		return (printf("Error getting current time\n"), -1);
	else
		return ((current_time.tv_sec * 1000) + (current_time.tv_usec / 1000));
}

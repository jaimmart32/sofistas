/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaimmart <jaimmart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 12:41:54 by jaimmart          #+#    #+#             */
/*   Updated: 2023/10/04 16:09:36 by jaimmart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*Sleeps time in miliseconds passed as parameter.
The usleep() function suspends the process for at least the number of
microseconds specified as an argument. The process may be suspended
for longer than the specified value.
If you make several shorter calls to usleep(), the overhead of
time is added several times, but it is small in each call.*/
void	ft_msleep(long time_in_ms)
{
	long	call_time;

	call_time = current_time();
	while (current_time() - call_time < time_in_ms)
		usleep(500);
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

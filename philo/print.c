/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaimmart <jaimmart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 12:05:50 by jaimmart          #+#    #+#             */
/*   Updated: 2023/10/06 12:06:52 by jaimmart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_death(t_philo *philo)
{
	long	curr_time;

	curr_time = current_time() - philo->sim_data->start_time;
	pthread_mutex_lock(&philo->sim_data->mutex_msg);
	printf("%li %i died\n", curr_time, philo->seat);
	pthread_mutex_unlock(&philo->sim_data->mutex_msg);
}

/* Print death has to be before check_end so that the msg is printed.*/
void	print_msg(long time, int msg, t_philo *philo)
{
	t_simu	*sim_data;

	sim_data = philo->sim_data;
	if (check_end(sim_data))
		return ;
	pthread_mutex_lock(&philo->sim_data->mutex_msg);
	pthread_mutex_lock(&philo->sim_data->mutex_end);
	if (!sim_data->end_simu && msg == FORK_MSG)
		printf("%li %i has taken a fork\n", time, philo->seat);
	if (!sim_data->end_simu && msg == EAT_MSG)
		printf("%li %i is eating\n", time, philo->seat);
	if (!sim_data->end_simu && msg == SLEEP_MSG)
		printf("%li %i is sleeping\n", time, philo->seat);
	if (!sim_data->end_simu && msg == THINK_MSG)
		printf("%li %i is thinking\n", time, philo->seat);
	pthread_mutex_unlock(&philo->sim_data->mutex_msg);
	pthread_mutex_unlock(&philo->sim_data->mutex_end);
}

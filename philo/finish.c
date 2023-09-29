/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   finish.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaimmart <jaimmart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 16:03:54 by jaimmart          #+#    #+#             */
/*   Updated: 2023/09/29 16:10:16 by jaimmart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*Destroy(free) mutex, free forks, philos and sim_data*/
void	free_for_all(t_simu *sim_data)
{
	int	i;

	i = -1;
	while (++i < sim_data->n_philos)
	{
		pthread_mutex_destroy(&sim_data->forks[i]);
	}
	free(sim_data->forks);
	free(sim_data->philos);
	free(sim_data);
}

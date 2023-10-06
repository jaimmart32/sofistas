/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   finish.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaimmart <jaimmart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 16:03:54 by jaimmart          #+#    #+#             */
/*   Updated: 2023/10/06 12:31:38 by jaimmart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	set_end_flag(t_simu *sim_data)
{
	pthread_mutex_lock(&sim_data->mutex_end);
	sim_data->end_simu = 1;
	pthread_mutex_unlock(&sim_data->mutex_end);
}

/*Destroy(free) mutex, free forks, philos and sim_data*/
void	free_for_all(t_simu *sim_data)
{
	int	i;

	i = -1;
	while (++i < sim_data->n_philos)
	{
		pthread_mutex_destroy(&sim_data->forks[i]);
		pthread_mutex_destroy(&sim_data->philos[i].mutex_to_live);
	}
	pthread_mutex_destroy(&sim_data->mutex_msg);
	pthread_mutex_destroy(&sim_data->mutex_end);
	pthread_mutex_destroy(&sim_data->mutex_finished_meals);
	free(sim_data->forks);
	free(sim_data->philos);
	free(sim_data);
}

int	check_end(t_simu *sim_data)
{
	int	end_simulation;

	end_simulation = 0;
	pthread_mutex_lock(&sim_data->mutex_end);
	if (sim_data->end_simu)
		end_simulation = 1;
	pthread_mutex_unlock(&sim_data->mutex_end);
	pthread_mutex_lock(&sim_data->mutex_finished_meals);
	if (sim_data->fin_meals == sim_data->n_philos)
	{
		set_end_flag(sim_data);
		end_simulation = 1;
	}
	pthread_mutex_unlock(&sim_data->mutex_finished_meals);
	if (end_simulation)
		return (1);
	return (0);
}

void	*check_death(void *arg)
{
	int		i;
	t_simu	*sim_data;
	t_philo	*philo;
	long	aux;

	sim_data = (t_simu *)arg;
	while (!check_end(sim_data))
	{
		i = 0;
		while (i < sim_data->n_philos)
		{
			philo = &sim_data->philos[i++];
			pthread_mutex_lock(&philo->mutex_to_live);
			aux = philo->to_live;
			pthread_mutex_unlock(&philo->mutex_to_live);
			if (current_time() > aux)
			{
				print_death(philo);
				set_end_flag(philo->sim_data);
				return (NULL);
			}
		}
	}
	return (NULL);
}

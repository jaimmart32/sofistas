/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   finish.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaimmart <jaimmart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 16:03:54 by jaimmart          #+#    #+#             */
/*   Updated: 2023/10/06 11:51:06 by jaimmart         ###   ########.fr       */
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
		pthread_mutex_lock(&sim_data->mutex_end);
		sim_data->end_simu = 1;
		end_simulation = 1;
		pthread_mutex_unlock(&sim_data->mutex_end);
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
				pthread_mutex_lock(&philo->sim_data->mutex_end);
				sim_data->end_simu = 1;
				pthread_mutex_unlock(&philo->sim_data->mutex_end);
				return (NULL);
			}
		}
	}
	return (NULL);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   finish.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaimmart <jaimmart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 16:03:54 by jaimmart          #+#    #+#             */
/*   Updated: 2023/10/02 17:47:56 by jaimmart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_msg(long time, int msg, t_philo *philo)
{
	t_simu	*sim_data;

	sim_data = philo->sim_data;
	if (check_end(philo))
		return ;
	if (!sim_data->end_simu && msg == FORK_MSG)
		printf("%li philo %i has taken a fork\n", time, philo->seat);
	if (!sim_data->end_simu && msg == EAT_MSG)
		printf("%li philo %i is eating\n", time, philo->seat);
	if (!sim_data->end_simu && msg == SLEEP_MSG)
		printf("%li philo %i is sleeping\n", time, philo->seat);
	if (!sim_data->end_simu && msg == THINK_MSG)
		printf("%li philo %i is thinking\n", time, philo->seat);
	if (!sim_data->end_simu && msg == DEATH_MSG)
		printf("%li philo %i died\n", time, philo->seat);
}

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

int	check_end(t_philo *philo)
{
	if (current_time() > philo->to_live)
		philo->sim_data->end_simu = 1;
	if (philo->sim_data->fin_meals == philo->sim_data->n_philos)
	{
		philo->sim_data->end_simu = 1;
		printf("All philos finished their meals\n");
	}
	if (philo->sim_data->end_simu)
		return (1);
	return (0);
}

void	*check_death(void *arg)
{
	int		i;
	t_simu	*sim_data;
	t_philo	*philo;
	long	curr_time;

	sim_data = (t_simu *)arg;
	while (1)
	{
		i = 0;
		while (i < sim_data->n_philos)
		{
			philo = &sim_data->philos[i++];
			if (current_time() > philo->to_live)
			{
				curr_time = current_time() - sim_data->start_time;
				print_msg(curr_time, DEATH_MSG, philo);
				sim_data->end_simu = 1;
				return (NULL);
			}
		}
	}
	return (NULL);
}

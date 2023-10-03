/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaimmart <jaimmart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 15:49:41 by jaimmart          #+#    #+#             */
/*   Updated: 2023/10/03 16:07:04 by jaimmart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	kill_lonely_philo(t_simu *sim_data)
{
	long	curr_time;

	curr_time = current_time() - sim_data->start_time;
	print_msg(curr_time, FORK_MSG, &sim_data->philos[0]);
	ft_msleep(sim_data->to_die);
	curr_time = current_time() - sim_data->start_time;
	print_msg(curr_time, DEATH_MSG, &sim_data->philos[0]);
}

void	ft_eat(t_philo *philo)
{
	long	curr_time;

	pthread_mutex_lock(&philo->sim_data->forks[philo->left]);
	curr_time = current_time() - philo->sim_data->start_time;
	print_msg(curr_time, FORK_MSG, philo);
	pthread_mutex_lock(&philo->sim_data->forks[philo->right]);
	curr_time = current_time() - philo->sim_data->start_time;
	print_msg(curr_time, FORK_MSG, philo);
	curr_time = current_time() - philo->sim_data->start_time;
	print_msg(curr_time, EAT_MSG, philo);
	philo->n_meals++;
	if (philo->n_meals == philo->sim_data->n_meals)
		philo->sim_data->fin_meals++;
	philo->to_live += philo->sim_data->to_die;
	ft_msleep(philo->sim_data->to_eat);
	pthread_mutex_unlock(&philo->sim_data->forks[philo->left]);
	pthread_mutex_unlock(&philo->sim_data->forks[philo->right]);
}

void	ft_sleep(t_philo *philo)
{
	long	curr_time;

	curr_time = current_time() - philo->sim_data->start_time;
	print_msg(curr_time, SLEEP_MSG, philo);
	ft_msleep(philo->sim_data->to_sleep);
}

void	ft_think(t_philo *philo)
{
	long	curr_time;

	curr_time = current_time() - philo->sim_data->start_time;
	print_msg(curr_time, THINK_MSG, philo);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->seat % 2 == 0)
		ft_msleep(42);
	while (!check_end(philo))
	{
		ft_eat(philo);
		if (philo->sim_data->end_simu)
			break ;
		ft_sleep(philo);
		if (philo->sim_data->end_simu)
			break ;
		ft_think(philo);
		if (philo->sim_data->end_simu)
			break ;
	}
	return (NULL);
}

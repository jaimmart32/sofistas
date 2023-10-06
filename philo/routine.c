/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaimmart <jaimmart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 15:49:41 by jaimmart          #+#    #+#             */
/*   Updated: 2023/10/05 16:57:36 by jaimmart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	kill_lonely_philo(t_simu *sim_data)
{
	long	curr_time;

	curr_time = current_time() - sim_data->start_time;
	print_msg(curr_time, FORK_MSG, &sim_data->philos[0]);
	ft_msleep(sim_data->to_die);
	print_death(&sim_data->philos[0]);
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
	{
		pthread_mutex_lock(&philo->sim_data->mutex_finished_meals);
		philo->sim_data->fin_meals++;
		pthread_mutex_unlock(&philo->sim_data->mutex_finished_meals);
	}
	pthread_mutex_lock(&philo->mutex_to_live);
	philo->to_live = current_time() + philo->sim_data->to_die;
	pthread_mutex_unlock(&philo->mutex_to_live);
	ft_msleep(philo->sim_data->to_eat);
}

void	ft_sleep(t_philo *philo)
{
	long	curr_time;

	curr_time = current_time() - philo->sim_data->start_time;
	print_msg(curr_time, SLEEP_MSG, philo);
	pthread_mutex_unlock(&philo->sim_data->forks[philo->left]);
	pthread_mutex_unlock(&philo->sim_data->forks[philo->right]);
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
	while (!check_end(philo->sim_data))
	{
		ft_eat(philo);
		ft_sleep(philo);
		ft_think(philo);
	}
	return (NULL);
}

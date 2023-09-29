/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaimmart <jaimmart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 15:49:41 by jaimmart          #+#    #+#             */
/*   Updated: 2023/09/29 12:13:32 by jaimmart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_eat(t_philo *philo)
{
	long	curr_time;

	curr_time = current_time() - philo->sim_data->start_time;
	printf("%li philo %i is eating\n", curr_time, philo->seat);
	ft_msleep(philo->sim_data->to_eat);
	philo->to_live += philo->sim_data->to_die;
	philo->n_meals++;
}

void	ft_sleep(t_philo *philo)
{
	long	curr_time;

	curr_time = current_time() - philo->sim_data->start_time;
	printf("%li philo %i is sleeping\n", curr_time, philo->seat);
	ft_msleep(philo->sim_data->to_sleep);
}

void	ft_think(t_philo *philo)
{
	long	curr_time;

	curr_time = current_time() - philo->sim_data->start_time;
	printf("%li philo %i is thinking\n", curr_time, philo->seat);
}

int	check_end(t_philo *philo)
{
	if (current_time() > philo->to_live)
	{
		printf("Philo %d muerto\n", philo->seat);
		return (1);
	}
	if (philo->n_meals == philo->sim_data->n_meals)
	{
		printf("Philo %d finished his meals\n", philo->seat);
		return (1);
	}
	return (0);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;

	while (!check_end(philo))
	{
		ft_eat(philo);
		ft_sleep(philo);
		ft_think(philo);
	}
	return (NULL);
}
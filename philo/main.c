/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaimmart <jaimmart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 11:43:44 by jaimmart          #+#    #+#             */
/*   Updated: 2023/10/04 16:20:33 by jaimmart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_simu	*init_simu(char **av)
{
	t_simu	*sim_data;

	sim_data = malloc(sizeof(t_simu));
	if (!sim_data)
		return (NULL);
	sim_data->n_philos = ft_atoi(av[1]);
	sim_data->to_die = ft_atoi(av[2]);
	sim_data->to_eat = ft_atoi(av[3]);
	sim_data->to_sleep = ft_atoi(av[4]);
	sim_data->n_meals = -42;
	if (av[5])
		sim_data->n_meals = ft_atoi(av[5]);
	sim_data->fin_meals = 0;
	sim_data->end_simu = 0;
	sim_data->start_time = current_time();
	sim_data->forks = malloc(sizeof(pthread_mutex_t) * sim_data->n_philos);
	if (sim_data->forks == NULL)
		return (free(sim_data), NULL);
	pthread_mutex_init(&sim_data->mutex_msg, NULL);
	pthread_mutex_init(&sim_data->mutex_end, NULL);
	pthread_mutex_init(&sim_data->mutex_finished_meals, NULL);
	return (sim_data);
}

t_philo	*init_philos(t_simu *sim_data)
{
	t_philo	*philos;
	int		i;

	philos = malloc(sizeof(t_philo) * sim_data->n_philos);
	if (!philos)
		return (NULL);
	i = -1;
	while (++i < sim_data->n_philos)
	{
		philos[i].seat = i + 1;
		philos[i].n_meals = 0;
		philos[i].to_live = current_time() + sim_data->to_die;
		philos[i].left = i;
		philos[i].right = i + 1;
		if (i + 1 == sim_data->n_philos)
			philos[i].right = 0;
		pthread_mutex_init(sim_data->forks + i, NULL);
		pthread_mutex_init(&philos[i].mutex_to_live, NULL);
		philos[i].sim_data = sim_data;
	}
	return (philos);
}

int	create_join_threads(t_simu *sim_data)
{
	int	i;

	if (sim_data->n_philos == 1)
		return (kill_lonely_philo(sim_data), 0);
	if (pthread_create(&sim_data->death_tid, NULL, &check_death,
			(void *)sim_data))
		return (1);
	pthread_detach(sim_data->death_tid);
	i = 0;
	while (i < sim_data->n_philos)
	{
		if (pthread_create(&sim_data->philos[i].tid, NULL,
				&routine, (void *)&sim_data->philos[i]))
			return (1);
		i++;
	}
	i = 0;
	while (i < sim_data->n_philos)
	{
		if (pthread_join(sim_data->philos[i].tid, NULL))
			return (1);
		i++;
	}
	return (0);
}

int	main(int ac, char **av)
{
	t_simu	*sim_data;
	t_philo	*philos;

	if (ac < 5 || ac > 6)
		printf("Invalid number of arguments\n");
	if (!check_args(ac, av))
		return (1);
	sim_data = init_simu(av);
	printf("start time = %li miliseconds\n", sim_data->start_time);
	if (!sim_data)
		return (1);
	philos = init_philos(sim_data);
	if (!philos)
		return (1);
	sim_data->philos = philos;
	if (create_join_threads(sim_data))
		return (1);
	free_for_all(sim_data);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaimmart <jaimmart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 11:52:40 by jaimmart          #+#    #+#             */
/*   Updated: 2023/09/29 16:09:31 by jaimmart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_philo
{
	pthread_t		tid;	
	int				seat;
	int				n_meals;
	long			to_live;
	int				left;
	int				right;
	struct s_simu	*sim_data;

}t_philo;


typedef struct s_simu
{
	int				n_philos;
	long			to_die;
	long			to_eat;
	long			to_sleep;
	int				n_meals;
	long			start_time;
	t_philo			*philos;
	pthread_mutex_t	*forks;
}t_simu;

/*	check_args.c	*/
int		ft_atoi(const char *str);
int		check_args(int ac, char **av);
/*	routine.c	*/
void	*routine(void *arg);
/*	time.c	*/
void	ft_msleep(long time_in_ms);
long	current_time(void);
/*	finish.c	*/
void	free_for_all(t_simu *sim_data);
#endif
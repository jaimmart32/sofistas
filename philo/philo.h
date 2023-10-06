/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaimmart <jaimmart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 11:52:40 by jaimmart          #+#    #+#             */
/*   Updated: 2023/10/06 12:08:43 by jaimmart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

# define FORK_MSG 1
# define EAT_MSG 2
# define SLEEP_MSG 3
# define THINK_MSG 4
# define DEATH_MSG 5

typedef struct s_philo
{
	pthread_t		tid;	
	int				seat;
	int				n_meals;
	long			to_live;
	int				left;
	int				right;
	pthread_mutex_t	mutex_to_live;
	struct s_simu	*sim_data;

}t_philo;

typedef struct s_simu
{
	int				n_philos;
	long			to_die;
	long			to_eat;
	long			to_sleep;
	int				n_meals;
	int				fin_meals;
	int				end_simu;
	long			start_time;
	pthread_t		death_tid;
	t_philo			*philos;
	pthread_mutex_t	*forks;
	pthread_mutex_t	mutex_msg;
	pthread_mutex_t	mutex_end;
	pthread_mutex_t	mutex_finished_meals;
}t_simu;

/*	check_args.c	*/
int		ft_atoi(const char *str);
int		check_args(int ac, char **av);
/*	routine.c	*/
void	kill_lonely_philo(t_simu *sim_data);
void	*routine(void *arg);
/*	time.c		*/
void	ft_msleep(long time_in_ms);
long	current_time(void);
/*	finish.c	*/
void	free_for_all(t_simu *sim_data);
int		check_end(t_simu *sim_data);
void	*check_death(void *arg);
/*	print.c		*/
void	print_death(t_philo *philo);
void	print_msg(long time, int msg, t_philo *philo);
#endif
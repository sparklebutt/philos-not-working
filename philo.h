/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araveala <araveala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 14:26:18 by araveala          #+#    #+#             */
/*   Updated: 2024/07/20 11:20:38 by araveala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

#include <stdio.h> //printf
#include <stdlib.h> //malloc
#include <unistd.h> //write //usleep
#include <sys/time.h>
#include <pthread.h>
#include <string.h>

// the philosopher
typedef  pthread_mutex_t t_mx; //amnything i plan on locking
typedef struct s_philosopher t_philosopher;
typedef struct s_data
{
	t_mx			*main_fork_lock;
	t_mx			ultima;

//	pthread			daddy_id;
	size_t			start_time;
	int				death_flag; //set
	
	int				num_of_philos; //set
	size_t				time_to_die; //set
	int				time_to_eat; //set
	int				time_to_sleep; //set
	int				num_of_meals; //set

	t_philosopher	 *philo;
}	t_data;


typedef struct s_philosopher
{
//	size_t		start_time;
	size_t		start_time;
	size_t		last_meal;

//	size_t		started_thinking;
//	int			*thinkning;

//	size_t		started_sleeping;
//	int			*sleeping;

//	size_t		time_of_death;
//	int			*dead;
	
//	size_t		start_of_meal; // start time of last meal milisec	
//	size_t		end_of_meal;
//	int			*eating; //might no need
	size_t			meals; // how many meals have been had
	pthread_t	thread_id;
	int			philo_id;
	int			death_flag;
	t_mx		*right_fork;
	t_mx		*left_fork;
	int			forks;
	t_data		*data;

}	t_philosopher;

typedef struct s_message
{

}	t_message;
	


typedef struct s_manager
{
	t_philosopher 	*philo;
	t_data			*data;
}	t_manager;

// user_input checks
int			argument_count(int	argc);
int			string_valid(char **argv);
int			check_input(int argc, char **argv);

// utils
long int	ft_atol(const char *str);
int			ft_isdigit(int c); //is char digit
int			ft_strlen(char *s);
size_t		get_time();
size_t		time_stamp(size_t now, t_data *data);//t_philosopher *philo);
// init data 
int			quick_check(long int num);//(t_data *data);
int			init_data(t_data *data, char **argv);
int			init_philo(t_data *data);
//main
int			main(int argc, char **argv);



// free things
void	free_mutex(t_data *data);
void	free_all(t_data *data);
//test functions delete me after plz
void	loop(t_data *d, int f);
#endif

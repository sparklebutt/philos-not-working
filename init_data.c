/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araveala <araveala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 11:37:03 by araveala          #+#    #+#             */
/*   Updated: 2024/07/20 12:53:17 by araveala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int quick_validity_check(t_data *data, int x)
{
	if (data->num_of_philos < 1)
	{
		printf("must have 1 or more philosoher\n"); //check check
		return (-1);
	}
	if (data->time_to_die < 0) 
		return (-1);
	if (data->time_to_eat == -1)  
		return (-1);
	if (data->time_to_sleep == -1) 
		return (-1);
	if (x == 0)
	{
		if (data->num_of_meals == -1 || data->num_of_meals == 0)
			return (-1);
	}
	else if (x == 1)
		data->num_of_meals = -10;
	return (1);
}

int quick_check(long int num)
{
	int diff;

	diff = 0;
	if (num <= 0)
	{
		printf("number cant be 0 or less\n");
		return (-1);
	}
	if (num < -2147483648 || num > 2147483647)
	{
		printf("system overload: number is larger than int\n");
		diff = num / (1000 * 60 * 60 * 24);
		printf("do you intend to spend %d days and wait\n", diff);
		return (-1);
	}
	else
		return ((int)num);
}
int	set_data_mutex(t_data *data)
{
	int i;

	i = 0;
	data->main_fork_lock = malloc(sizeof(t_mx) * data->num_of_philos);
	if (data->main_fork_lock == NULL)
		return (1);
	while (i < data->num_of_philos)
	{
		pthread_mutex_init(&data->main_fork_lock[i], NULL);
		i++;
	}
	pthread_mutex_init(&data->ultima, NULL);
	return (0);
}

int init_data(t_data *data, char **argv)
{
	int x;
	
	x = 1;
	data->num_of_philos = quick_check(ft_atol(argv[1]));
	data->time_to_die = quick_check(ft_atol(argv[2]));
	data->time_to_eat = quick_check(ft_atol(argv[3]));
	data->time_to_sleep = quick_check(ft_atol(argv[4]));
	data->start_time = get_time();
	data->death_flag = 0;
	if (argv[5] != NULL)
	{
		data->num_of_meals = quick_check(ft_atol(argv[5])); // can this be 0
		x = 0;
	}
	if (quick_validity_check(data, x) == -1)
		return (1);
	if(set_data_mutex(data) == 1)
		return (1);

	return (0);
}

int		init_philo(t_data *data)
{
	int i;

	i = 0;
	data->philo = malloc (data->num_of_philos * (sizeof(t_philosopher)));//need a null?
	if (data->philo == NULL)
	{
		free(data);
		return (1); //exit
	}
	while (i < data->num_of_philos) // =
	{
		data->philo[i].philo_id = i + 1;
		data->philo[i].meals = 0;
		data->philo[i].data = data;
		data->philo[i].right_fork =  &data->main_fork_lock[i];
		data->philo[i].left_fork = &data->main_fork_lock[i + 1 % data->num_of_philos];

		//	data->philo[i].start_time = 0;
		data->philo[i].last_meal = 0;
		data->philo[i].forks = 0;
		data->philo[i].death_flag = 0;
		i++;


	}
	return (0);
}

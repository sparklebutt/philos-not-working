/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araveala <araveala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 14:37:42 by araveala          #+#    #+#             */
/*   Updated: 2024/07/23 12:32:16 by araveala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void		print_message(char *str, t_philosopher *t_philo, t_data *data)
{
	pthread_mutex_lock(&data->ultima);
	printf("%zu %d %s", time_stamp(get_time(), data), t_philo->philo_id, str);
	pthread_mutex_unlock(&data->ultima);
}

void		new_sleep(t_data *data, size_t wait)
{
    size_t    now;

    now = time_stamp(get_time(), data);
    while ((time_stamp(get_time(), data) - now) < wait)
        usleep(500);

}

void	check_dead(t_data *data, t_philosopher *philo)
{
	size_t now;

	pthread_mutex_lock(&data->ultima);
	now = time_stamp(get_time(), data);
	if (now - philo->last_meal >= data->time_to_die)
	{
		printf("%zu %d died\n", (now - philo->last_meal), philo->philo_id);	
		data->death_flag = 1;	
	}
	pthread_mutex_unlock(&data->ultima);
}

void	check_check(t_data *data, t_philosopher *philo)
{
	int i;

	i = 0;


	while (data->death_flag == 0 && i < data->num_of_philos)
	{
		check_dead(data, &philo[i]);
		if (data->death_flag == 1)
		{
			printf("broken from checkcheck");
			break;
		}
		i++;
	}
	return;
}

int eating(t_data *data, t_philosopher *t_philo)
{
//	check_dead(data, t_philo);
	if(data->death_flag == 1)
		return (0);
	print_message("is eating\n", t_philo, data);
	t_philo->last_meal = time_stamp(get_time(), data);
	new_sleep(data, data->time_to_eat);

//	check_dead(data, t_philo);
	if(data->death_flag == 1)
		return (0);
	pthread_mutex_unlock(t_philo->right_fork);
	pthread_mutex_unlock(t_philo->left_fork);

//	check_dead(data, t_philo);
	if(data->death_flag == 1)
		return (0);
	print_message("is sleeping\n", t_philo, data);
	new_sleep(data, data->time_to_sleep);
//	check_dead(data, t_philo);
	if(data->death_flag == 1)
		return (0);
	print_message("is thinking\n", t_philo, data);
	if(data->death_flag == 1)
		return (0);

	return (1);
}

int	forks(t_data *data, t_philosopher *t_philo)
{

	check_dead(data, t_philo);

	if (data->death_flag == 1)
		return (0);
	if (t_philo->philo_id % 2 != 0)// && t_philo->right_fork < t_philo->left_fork)/// and
	{
		pthread_mutex_lock(t_philo->right_fork);
		print_message("has taken fork\n", t_philo, data);
	}
	else //if (t_philo->right_fork > t_philo->left_fork)
	{
		pthread_mutex_lock(t_philo->left_fork);
		print_message("has taken fork\n", t_philo, data);	
	}
	if (t_philo->philo_id % 2 != 0)// && t_philo->right_fork < t_philo->left_fork)
	{
		
		if (pthread_mutex_lock(t_philo->left_fork) != 0)
		{
			pthread_mutex_unlock(t_philo->right_fork);
			return (0) ;
		}
		print_message("has taken fork\n", t_philo, data);
	}
	else //if (t_philo->right_fork > t_philo->left_fork)
	{
		if (pthread_mutex_lock(t_philo->right_fork) != 0)
		{		
			pthread_mutex_unlock(t_philo->left_fork);				   
			return(0) ;
		}
		print_message("has taken fork\n", t_philo, data);	
	}
	return (1);
}

void	*actions(void *data)
{
	t_data			*t_data;
	t_philosopher	*t_philo;

	t_philo = (t_philosopher *)data;
	t_data = t_philo->data;

	while (t_data->death_flag == 0)
	{
//		if (t_philo->philo_id % 2 != 0)
//			usleep(1000);

		if(forks(t_data, t_philo) == 0)
			break;
		if(eating(t_data, t_philo) == 0)
			break;
//		usleep(600000);
	}
	return (NULL);
}

int join_threads(t_data *data)
{
	int i;
	
	i = 0;
	while(i < data->num_of_philos)
	{
		pthread_join(data->philo[i].thread_id, NULL);
		i++;
	}
	return (0);
}

int	create_threads(t_data *data)
{
	int i;
	
	i = 0;
	
//	data->start_time = get_time();	
	while(i < data->num_of_philos)
	{
		if (pthread_create(&data->philo[i].thread_id, NULL, &actions, &data->philo[i]) != 0)
		{
			printf("threaad creation issue\n");
			return (1);
		}
		i++;
	}
//	join_threads(data);
	while (data->death_flag == 0)
	{
		check_check(data, data->philo);
		if (data->death_flag == 1)
			break ;
	}
	join_threads(data);
	return (1);
}

int main(int argc, char **argv)
{
	static 	t_data *data;
	if (check_input(argc, argv) == 1)
		exit(1);
	data = malloc(sizeof(t_data) * 1);
	if (data == NULL)
		return (1); //exit
	if (init_data(data, argv) == 1)
	{
		free(data);
		exit(1);
	}
	init_philo(data);
	create_threads(data);
//	daddy(data);
//	join_threads(data);
//	free_all(data);
	return (0);
}

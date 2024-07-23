/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araveala <araveala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 14:50:26 by araveala          #+#    #+#             */
/*   Updated: 2024/07/20 10:25:24 by araveala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_isdigit(int c)
{
	if (c >= 0060 && c <= 0071)
		return (1);
	return (0);
}

int	ft_strlen(char *s)
{
	int i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

size_t	time_stamp(size_t now, t_data *data)//t_philosopher *philo) //t_data *data, 
{

	size_t ret;
//	(end.tv_sec - time.tv_sec) * 1000 + (end.tv_usec - time.tv_usec) / 1000;
//	ret = philo->eating_time - philo->start_time;
	ret = now - data->start_time;
//	ret = now - philo->start_time;
//	philo->start_time = get_time();
	return(ret);
//	printf("%zu philo %d nonom \n", ret, philo->philo_id);
}

size_t get_time()
{
	struct timeval time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

long int	ft_atol(const char *str)
{
	int			save;
	long int	set_num;

	save = 1;
	set_num = 0;
	while (*str != '\0')
	{
		while ((*str > 8 && *str < 14) || *str == 32)
			str++;
		if (*str == '+' || *str == '-')
		{
			if (*str == '-')
				save = -1;
			str++;
		}
		while (ft_isdigit(*str) == 1)
		{
			set_num = set_num * 10 + *str - 48;
			str++;
		}
		return (set_num * save);
	}
	return (-1); // int min -1
}



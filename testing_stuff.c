#include "philo.h"

void	loop(t_data *d, int f)
{

	printf("number of philos = %d\n", d->num_of_philos);
	printf("time to die = %d\n", d->time_to_die);
	printf("time to eat = %d\n", d->time_to_eat);
	printf("time to sleep = %d\n", d->time_to_sleep);
	if (f == 0)
		printf("num of meals = %d\n", d->num_of_meals);
}

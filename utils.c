#include "philo.h"

int	ft_atoi(const char *str)
{
	long int	n;
	int		sign;

	n = 0;
	sign = 1;
	while ((*str <= 13 && *str >= 9) || *str == 32)
		str++;
	if (*str == '-')
		return (-1);
	else if (*str == '+')
		str++;
	while (*str)
	{
		if (*str >= '0' && *str <= '9')
			n = n * 10 + (*str++ - '0');
		else
			return (-1);
	}
	return ((int)(n * sign));
}

long long	timestamp(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return ((t.tv_sec * 1000) + (t.tv_usec / 1000));
}

long long	time_diff(long long prev, long long now)
{
	return (now - prev);
}

void	smart_sleep(long long time, t_rules *rules)
{
	long long	i;
	long long	time_check;

	i = timestamp();
	while (!(rules->dead))
	{
		time_check = time_diff(i, timestamp());
		if (time_check >= time)
			break;
		usleep(50);
	}
}

void	print(t_rules *rules, int id, char *str)
{
	pthread_mutex_lock(&(rules->write));
	if (!(rules->dead))
	{
		printf("%lli ", timestamp() - rules->f_time);
		printf("Philo[%d] ", id + 1);
		printf("%s\n", str);
	}
	pthread_mutex_unlock(&(rules->write));
}











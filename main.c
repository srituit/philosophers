#include "philo.h"

int	init_philo(t_rules *rules)
{
	int	i;

	i = rules->nb_p;
	while (--i >= 0)
	{
		rules->philo[i].id = i;
		rules->philo[i].ate = 0;
		rules->philo[i].left_fork = i;
		rules->philo[i].right_fork = (i + 1) % rules->nb_p;
		rules->philo[i].last_meal = 0;
		rules->philo[i].rules = rules;
	}
	return (0);
}

int	init_mutex(t_rules *rules)
{
	int	i;
	int	res;

	i = rules->nb_p;
	while (--i >= 0)
	{
		res = pthread_mutex_init(&(rules->fork[i]), NULL);
		if (res)
			return (1);
	}
	res = pthread_mutex_init(&(rules->write), NULL);
	if (res)
		return (2);
	res = pthread_mutex_init(&(rules->check_eat), NULL);
	if (res)
		return (3);
	return (0);
}

int	init(t_rules *rules, char **argv)
{
	int	res;

	rules->nb_p = ft_atoi(argv[1]);
	rules->t_die = ft_atoi(argv[2]);
	rules->t_eat = ft_atoi(argv[3]);
	rules->t_sleep = ft_atoi(argv[4]);
	rules->all_feed = 0;
	rules->dead = 0;
	if (rules->nb_p < 2 || rules->t_die < 0 || rules->t_eat < 0
		|| rules->t_sleep < 0 || rules->nb_p > 250)
		return (1);
	if (argv[5])
	{
		rules->nb_eat = ft_atoi(argv[5]);
		if (rules->nb_eat <= 0)
			return (1);
	}
	else
		rules->nb_eat = -1;
	res = init_mutex(rules);
	if (res)
		return (2);
	res = init_philo(rules);
	if (res)
		return (3);
	return (0);
}

int	main(int argc, char **argv)
{
	t_rules	rules;
	int	res;

	if (argc != 5 && argc != 6)
	{
		printf("Need 5 or 6 arg\n");
		return (1);
	}
	res = init(&rules, argv);
	if (res)
		return (2);
	res = l_philo(&rules);
	if (res)
		return (3);
	return (0);
}

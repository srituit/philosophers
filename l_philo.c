#include "philo.h"

void	exit_philo(t_rules *rules, t_philo *philo)
{
	int	i;

	i = 0;
	while (i < rules->nb_p)
	{
		pthread_join(philo[i].t_id, NULL);
		i++;
	}
	i = 0;
	while (i < rules->nb_p)
	{
		pthread_mutex_destroy(&(rules->fork[i]));
		i++;
	}
	pthread_mutex_destroy(&(rules->write));
}

void	dead_philo(t_rules *rules, t_philo *philo)
{
	int		i;
	long long	time_check;

	while (!(rules->all_feed))
	{
		i = -1;
		while (++i < rules->nb_p && !(rules->dead))
		{
			pthread_mutex_lock(&(rules->check_eat));
			time_check = time_diff(philo[i].last_meal, timestamp());
			if (time_check > rules->t_die)
			{
				print(rules, philo->id, "died");
				rules->dead = 1;
			}
			pthread_mutex_unlock(&(rules->check_eat));
			usleep(1000);
		}
		if (rules->dead)
			break ;
		i = 0;
		while (rules->nb_eat != -1 && i < rules->nb_p && philo[i].ate >= rules->nb_eat)
			i++;
		if (i == rules->nb_p)
			rules->all_feed = 1;
	}

}

void	philo_eat(t_philo *philo)
{
	t_rules	*rules;

	rules = philo->rules;
	pthread_mutex_lock(&(rules->fork[philo->left_fork]));
	print(rules, philo->id, "has taken a fork");
	pthread_mutex_lock(&(rules->fork[philo->right_fork]));
	print(rules, philo->id, "has taken a fork");
	pthread_mutex_lock(&(rules->check_eat));
	print(rules, philo->id, "is eating");
	philo->last_meal = timestamp();
	pthread_mutex_unlock(&(rules->check_eat));
	smart_sleep(rules->t_eat, rules);
	(philo->ate)++;
	pthread_mutex_unlock(&(rules->fork[philo->left_fork]));
	pthread_mutex_unlock(&(rules->fork[philo->right_fork]));
}

void	*philo_thread(void *void_philo)
{
	t_philo	*p;
	t_rules	*rules;

	p = (t_philo *) void_philo;
	rules = p->rules;
	if (p->id % 2 == 1)
		usleep(1000);
	while (!(rules->dead))
	{
		philo_eat(p);
		if (rules->all_feed)
			break ;
		print(rules, p->id, "is sleeping");
		smart_sleep(rules->t_sleep, rules);
		print(rules, p->id, "is thinking");
	}
	return (NULL);
}

int	l_philo(t_rules *rules)
{
	int	i;
	int	res;
	t_philo	*p;

	i = 0;
	p = rules->philo;
	rules->f_time = timestamp();
	while (i < rules->nb_p)
	{
		res = pthread_create(&(p[i].t_id), NULL, philo_thread, &(p[i]));
		if (res)
			return (1);
		p[i].last_meal = timestamp();
		i++;
	}
	dead_philo(rules, rules->philo);
	exit_philo(rules, p);
	return (0);
}

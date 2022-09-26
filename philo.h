#ifndef PHILO_H
# define PHILO_H


#include <sys/time.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

struct s_rules;

typedef struct s_philo
{
	int		id;
	int		ate;
	int		left_fork;
	int		right_fork;
	long long	last_meal;
	struct s_rules	*rules;
	pthread_t	t_id;
}	t_philo;

typedef struct s_rules
{
	int		nb_p;
	int		t_die;
	int		t_eat;
	int		t_sleep;
	int		nb_eat;
	int		dead;
	int		all_feed;
	long long	f_time;
	pthread_mutex_t	check_eat;
	pthread_mutex_t	fork[250];
	pthread_mutex_t	write;
	t_philo		philo[250];
}	t_rules;

int		ft_atoi(const char *str);
int		l_philo(t_rules *rules);
int		init(t_rules *rules, char **argv);
void		print(t_rules *rules, int id, char *str);
long long	timestamp(void);
long long	time_diff(long long prev, long long now);
void		smart_sleep(long long time, t_rules *rules);
void		exit_philo(t_rules *rules, t_philo *philo);
void		dead_philo(t_rules *rules, t_philo *philo);

#endif

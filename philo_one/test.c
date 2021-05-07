#include "philo_one.h"

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int mails = 0;
pthread_mutex_t mutex;

void	*routine()
{
	int i = -1;
	while (++i < 10000000)
	{
		pthread_mutex_lock(&mutex);
		mails++;
		pthread_mutex_unlock(&mutex);
	}
	return (NULL);
}

int main(void)
{
	pthread_t t1, t2;
	pthread_mutex_init(&mutex, NULL);
	if (pthread_create(&t1, NULL, &routine, NULL) < 0)
		return (1);
	if (pthread_create(&t2, NULL, &routine, NULL) < 0)
		return (2);
	if (pthread_join(t1, NULL) < 0)
		return (3);
	if (pthread_join(t2, NULL) < 0)
		return (4);
	pthread_mutex_destroy(&mutex);
	printf("Number of mails: %d\n", mails);
	return 0;
}

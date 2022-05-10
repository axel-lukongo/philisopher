# include <stdio.h>
# include <pthread.h>
# include <unistd.h>
# include <sys/time.h>
# include <stdlib.h>
# include <string.h>

void *func1(void * arg)
{
	while (1)
	{
		sleep(1);
		printf("1\n");
	}
	return (NULL);
	//pthread_exit(NULL);
}

void *func2(void * arg)
{
	while (1)
	{
		sleep(1);
		printf("2\n");
	}
	return (NULL);
	//pthread_exit(NULL);
}
int main()
{
	pthread_t t1;

	pthread_create(&t1, NULL, func2, NULL);
	func1(NULL);
	//pthread_create(&t2, NULL, func2, NULL);

	return(0);
}
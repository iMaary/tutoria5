#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int **readValues(int size);
void *increment(void *arg);
int sum = 0;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

int main(void) {
	int size = 0;

	scanf("%d", &size);
	
	pthread_t threads[size];
	int **matrix = readValues(size);

	for (int i = 0; i < size; i++) {
		int *lines = malloc(size * sizeof(int));

		if (pthread_create(&(threads[i]), NULL, increment, (void *)lines))
			printf("Thread %d not created", i);

		for (int j = 0; j < size; j++)
			lines[j] = matrix[i][j];
	}

	for (int i = 0; i < size; i++)
		pthread_join(threads[i], NULL);

	printf("%d\n", sum);
	
	return 0;
}

void *increment(void *arg) {
	int *lines = (int *)arg;      
        int size = sizeof(*lines);

	int this_sum = 0;

    	for(int i = 0; i < size; i++)
        	this_sum += lines[i];

	pthread_mutex_lock(&mutex);
	sum += this_sum;
	pthread_mutex_unlock(&mutex);
	return arg;
}


int **readValues(int size) {
	int **matrix = (int **)malloc(size * sizeof(int *));

	for (int i = 0; i < size; i++) {
		matrix[i] = (int *)malloc(size * sizeof(int));
		for (int j = 0; j < size; j++)
                        scanf("%d", &matrix[i][j]);
	}

	return matrix;	
}

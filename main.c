#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "mutex.h"
#define MAX 10

pthread_mutex_t mutex;
pthread_cond_t condConsumidor;
pthread_cond_t condProdutor;
int buffer = 0;

void *produtor() {
  int i;
	
	for(i = 0; i <= MAX; i++){
		lock(&mutex)
		while( buffer != 0) {
			wait(&condProdutor)
		}	
		buffer = i;
		signal(&condProdutor);
		unlock(&mutex);
	}
	pthread_exit(0);
}

void *consumidor() {
	int i;
	
	for(i = 0; i <= MAX; i++){
		lock(&mutex);
		while(buffer == 0) {
			wait(&condConsumidor, &mutex);
		}
		buffer = 0;
		signal(&condConsumidor);
		unlock(&mutex);
	}
	pthread_exit(0);
}

int main() {
	pthread_t produtor, consumidor;
	pthread_mutex_init(&mutex, 0);
	pthread_cond_init(&condProdutor, 0);
	pthread_cond_init(&condConsumidor, 0);
	pthread_create(&condProdutor, 0, produtor);
	pthread_create(&condConsumidor, 0, consumidor);
	pthread_join(produtor, 0);
	pthread_join(consumidor, 0);
	pthread_cond_destroy(&condProdutor, 0);
	pthread_cond_destroy(&condConsumidor, 0);
	pthread_mutex_destroy(&mutex, 0);
}


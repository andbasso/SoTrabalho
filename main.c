#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "mutex.h"

#define N_ITENS 10
int buffer[N_ITENS];

int mutex = 0, consumido = 0, produzido = 0, cont = 0, inicio = 0, final = 0;

void* produtor(void *v) {
  int i;
  
  for (i = 0; i < 3 * N_ITENS; i++) {
	  while (cont == 10) ;
      if(mutex == 0) {
	    //mutex++;
		lock(mutex);
        printf("Produtor, item = %d, mutex = %d", i, mutex);     
        final = (final + 1) % N_ITENS;
		if(buffer[final] != 0)
			printf("posicao ocupada ERROR");
        buffer[final] = 1;
		produzido++;
		cont++;
        //mutex--;
		unlock(mutex);
		printf(" mutexF = %d\n", mutex);     
      }
	sleep(random() % 5);
  }
  
  return NULL;
}

void* consumidor(void *v) {
  int i, consumir;

  for (i = 0; i < 3 * N_ITENS; i++) {
	while (cont == 0);
    if(mutex == 0){
        //mutex++;
        lock(mutex);
        inicio = (inicio + 1) % N_ITENS;
        consumir = buffer[inicio];
		if(buffer[inicio] != 1)
			printf("posicao sem nada ERROR");
		buffer[inicio] = 0;
		consumido++;
        printf("Consumidor, item = %d, mutex = %d", i, mutex);     ;
        if (consumido > produzido)
            printf("Erro: item foi consumido antes de ser produzido.\n");
		cont--;
        unlock(mutex);
		printf(" mutexF = %d\n", mutex);     
    }
	sleep(random() % 5);
  }
  return NULL;
}

int main() {
  int i;
  
  pthread_t thr_produtor, thr_consumidor;

  /* Limpa o buffer */
  for (i = 0; i < N_ITENS; i++)
    buffer[i] = 0;
  
  pthread_create(&thr_produtor, NULL, produtor, NULL);
  pthread_create(&thr_consumidor, NULL, consumidor, NULL);

  pthread_join(thr_produtor, NULL); 
  pthread_join(thr_consumidor, NULL);

  return 0;
}


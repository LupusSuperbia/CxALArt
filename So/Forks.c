
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>

#define NUM_FILOSOFOS 5
#define NUM_COMIDAS 7
//Mutex para los tenedores
pthread_mutex_t tenedores[NUM_FILOSOFOS];
int comidas = 0;
void* filosofar(void* arg){
    int indice = *(int*)arg;

    while(!(comidas > NUM_COMIDAS)){
        printf("Filósofo %d está pensando.\n", indice);
        sleep(rand() % 3 + 1); // Simulamos el tiempo pensando

        // adquirimos los tenedores que estan tanto del
        // lado izquierdo como derecho
        int izq = indice;
        int der = (indice + 1) % NUM_FILOSOFOS;

        pthread_mutex_lock(&tenedores[izq]); // intentamos adquirir el tenedor izquierdo
        // esto lo hacemos buscando la posición de memoria de este tenedor
        printf("Filosofo %d ha tomado el tenedor %d.\n", indice, izq);
        pthread_mutex_lock(&tenedores[der]); // intentamos adquirir el tenedor derecho
        // esto lo hacemos buscando la posición de memoria de este tenedor
        printf("Filosofo %d ha tomado el tenedor %d.\n", indice, der);

        // Comé
        printf("Filosfo %d esta comiendo.\n", indice);

        // Liberar tenedores
          pthread_mutex_unlock(&tenedores[der]);
          pthread_mutex_unlock(&tenedores[izq]);
          printf("Filósofo %d ha dejado el tenedor %d.\n", indice, izq);
          printf("Filósofo %d ha dejado el tenedor %d.\n", indice, der);
        comidas++;
    }

    return NULL;
}

int main(){
    pthread_t filosofos[NUM_FILOSOFOS];
    int indices[NUM_FILOSOFOS];

    for (int i = 0; i < NUM_FILOSOFOS; i++){
        pthread_mutex_init(&tenedores[i], NULL);
    }

    srand(time(NULL));

    for (int i = 0; i < NUM_FILOSOFOS; i++) {
            indices[i] = i;
            pthread_create(&filosofos[i], NULL, filosofar, &indices[i]);
        }
    // Esperar a que terminen los hilos (en este caso, nunca terminan)
      for (int i = 0; i < NUM_FILOSOFOS; i++) {
          pthread_join(filosofos[i], NULL);
      }

      // Limpiar mutexes (nunca se alcanza en este caso)
      for (int i = 0; i < NUM_FILOSOFOS; i++) {
          pthread_mutex_destroy(&tenedores[i]);
      }
      printf("Se ha termnado");
      return 0;
}

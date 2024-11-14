#include <fcntl.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int main(void) {
  FILE *archivo;
  int contador = 0;
  printf("%d \n", contador);
  archivo = fopen("archivo.txt", "w");

  if (archivo == NULL) {
    printf("Error al abrir archivo\n");
    return 1;
  }
  // Abrir o crear un semáforo con un valor inicial de 1
  sem_t *sem = sem_open("/mysem", O_CREAT, 0666, 1);
  if (sem == SEM_FAILED) {
    perror("Error al crear el semáforo");
    return 1;
  }
  pid_t pid = fork();

  printf("%d", pid);
  if (pid == -1) {
    perror("Error al crear el proceso hijo");
    return 1;
  }

  if (pid == 0) {
    // Proceso
    printf("Hijo esperando en el semáforo\n");
    if (sem_wait(sem) == -1) {
      perror("Error al esperar en el semáforo");
      return 1;
    }
    printf("Hijo obtiene el semáforo\n");
    printf("Hijo accediendo al recurso compartido\n");
    sleep(1);
    fprintf(archivo, "Buenas noches dijo el hijo a su padre\n");
    printf("Hijo liberando el semáforo\n");
    if (sem_post(sem) == -1) {
      perror("Error al liberar el semáforo");
      return 1;
    }
  }
  pid_t pid2 = fork();

  printf("%d", pid2);
  if (pid2 == -1) {
    perror("Error al crear el proceso hijo");
    return 1;
  }
  if (pid2 == 0) {
    // Proceso
    printf("Hijo2 esperando en el semáforo\n");
    if (sem_wait(sem) == -1) {
      perror("Error al esperar en el semáforo");
      return 1;
    }
    printf("Hijo2 obtiene el semáforo\n");
    printf("Hijo2 accediendo al recurso compartido\n");
    sleep(1);
    fprintf(archivo, "Buenas noches dijo el hijo2 a su padre\n");
    printf("Hijo2 liberando el semáforo\n");
    if (sem_post(sem) == -1) {
      perror("Error al liberar el semáforo");
      return 1;
    }

  } else {
    // Proceso padre
    printf("Padre obtiene el semáforo\n");
    printf("Padre accediendo al recurso compartido\n");

    sleep(1);
    fprintf(archivo, "Buenas noches dijooo el padre a su hijo\n");
    printf("Padre liberando el semáforo\n");
    if (sem_post(sem) == -1) {
      perror("Error al liberar el semáforo");
      return 1;
    }

    int status;
    waitpid(pid, &status, 0);
    waitpid(pid2, &status, 0);

  }
  ++contador;
  fclose(archivo);
  // Cerrar y eliminar el semáforo
  if (sem_close(sem) == -1) {
    perror("Error al cerrar el semáforo");
    return 1;
  }
  if (sem_unlink("/mysem") == -1) {
    perror("Error al eliminar el semáforo");
    return (1);
  }

  return (0);
}

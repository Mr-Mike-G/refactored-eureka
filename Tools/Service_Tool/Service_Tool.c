#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include <semaphore.h>

int N=0;
sem_t s;
sem_t u;

typedef enum { start, stop, end, err } command;

command sceltaComando(char* cmd);
void stampaServizi(char*** services);

void* refresh(void* arg){
  char*** services= (char***) arg;
  printf("\033[H\033[J");
  printf("Stato servizi:\n");
  while(1){
    sem_wait(&s);
    stampaServizi(services);
    printf("\nPremi INVIO per inserire un comando.");
    sem_post(&s);
    sem_wait(&u);
    sem_post(&u);
  }
}

int main() {
    printf("\033[H\033[J");
    char command[100], word[100];
    int maxN = 5;
    int c;
    FILE* fp = NULL;
    char** services;
    
    //inizializzo i semafori
    sem_init(&s, 0, 1);
    sem_init(&u, 0, 1);
    
    //carico i servizi dal file 'services.txt'
    services = malloc(maxN * sizeof(char*));
    for (int i = 0; i < maxN; i++) services[i] = NULL;
    fp = fopen("services.txt", "r");
    if (fp == NULL) {
      printf("File \'services.txt\' non presente.\n");
      exit(0);
    }
    while (fscanf(fp, "%s", word) != EOF) {
      if (N + 1 > maxN) {
        maxN = maxN + maxN / 2;
        services = realloc(services, maxN * sizeof(char*));
      }
      services[N] = malloc(50 * sizeof(char));
      strcpy(services[N], word);
      N++;
    }
    fclose(fp);
    
    
    //generazione thread per l'output e ciclo sui comandi
    pthread_t t;
    pthread_create(&t, NULL, refresh, (void *) &services);
    while(c!=end){
	  c=err;
      fscanf(stdin,"%*c");
      sem_wait(&u);
      sem_wait(&s);
      sem_post(&u);
      printf("\033[H\033[J");
      printf("Stato servizi:\n");
      stampaServizi(&services);
      printf("\n\nLista comandi:\n- start <nome_servizio> , permette di avviare un servizio\n- stop <nome_servizio> , permette di chiudere un servizio\n- end , permette di terminare il programma\n\n");
      printf("Inserisci un comando: ");
      fgets(command, 100, stdin);
      sscanf(command, "%s", word);
      c = sceltaComando(word);
      switch (c){
        case start:
          sscanf(command, "%*s %s", word);
          strcpy(command,"systemctl start ");
          strcat(command, word);
          system(command);
        break;
        case stop:
          sscanf(command, "%*s %s", word);
          strcpy(command,"systemctl stop ");
          strcat(command, word);
          system(command);
        break;
        case err:
          printf("Comando inesistente\n");
        break;
      }
      sem_post(&s);
    }
    return 0;
}

command sceltaComando(char* cmd) {
    char tab[err][20] = { "start", "stop", "end" };
    int i;
    for (i = 0; i < err && strcmp(cmd, tab[i]); i++);
    return i;
}

void stampaServizi(char*** services){
  char cmd[150];
  printf("\033[2;1H");
  for(int i=0;i<N;i++){
    //genero la riga di comando da eseguire
    strcpy(cmd,"/bin/systemctl status ");
    strcat(cmd, (*services)[i]);
    strcat(cmd, " | grep Active: | tr -s \" \" | cut -f 4 -d \" \"");
    
    //leggo l'output restituito
    FILE *fp;
    char path[300];
    fp = popen(cmd, "r");
    if (fp == NULL) {
      printf("Errore nell'eseguire il comando\n" );
      exit(1);
    }
    while (fgets(path, 300, fp) != NULL) {
      sscanf(path,"%s",path);
      printf("- %s %s                 \n", (*services)[i], path);
    }
    pclose(fp);
  }
}
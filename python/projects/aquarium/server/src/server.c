#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<sys/errno.h>
#include<netinet/in.h>
#include<string.h>
#include <arpa/inet.h>
#include <fcntl.h> // for open
#include <unistd.h> // for close
#include<pthread.h>
#include<signal.h>

#include "aquarium.h"
#include "parser.h"

#define THREADS 10
#define SERVER_ADDRESS "127.0.0.1"


typedef struct {
  int port;
  int display_timeout_value;
  int fish_update_interval;
} controller_t;

aquarium_t *a;
controller_t controller;
FILE *server_log;

/* closes the log file if the server receives a ctrl-c */
void process_end() {
  if (server_log != NULL)
    fclose(server_log);
  exit(0);
}

/* changes the signal gestion to call process_end when receiving a ctrl-c */
void signal_gestion() {

  struct sigaction sa_int;

  sa_int.sa_handler = process_end;

  sigemptyset(&sa_int.sa_mask); // la masque est vide

  sa_int.sa_flags = 0; // pas d'options

  sigaction(SIGINT , &sa_int, NULL); // change le gestionnaire de signaux
}

/* opens the server log file */
int start_log() {

  server_log = fopen("log_server.txt", "w");
  if (server_log == NULL) {
    printf("Error starting log\n");
    return -1;
  }

  fprintf(server_log, "Log started\n");
  signal_gestion();
  return 0;
}

/* reads the configuration file */
void read_conf() {

  FILE *conf = fopen("../controller.cfg", "r");
  char buffer[BUFFER_SIZE];
  int i = 0;

  while (fgets(buffer, sizeof buffer, conf)) {

    strtok(buffer, "= ");
    strtok(NULL, " ");
    switch (i) {
    case 0: controller.port = atoi(strtok(NULL, "")); break;
    case 1: controller.display_timeout_value = atoi(strtok(NULL, "")); break;
    case 2: controller.fish_update_interval = atoi(strtok(NULL, "")); break;
    }

    i++;

  }

  fclose(conf);

  fprintf(server_log, "Configurations file read : [%d, %d, %d]\n", controller.port, controller.display_timeout_value, controller.fish_update_interval);
}


/* controls the prompt inputs at the server */
void * prompt_thread(void *arg) {

  a = create_aquarium();

  char buffer[100];
  do {
    fgets(buffer, BUFFER_SIZE, stdin);
    handle_input(buffer, &a);
  }while (strcmp(buffer, "") != 0);

  return 0;
}

/* controls the client inputs received by socket */
void * socket_thread(void *arg) {

  int socket = *((int *)arg);
  char client_message[BUFFER_SIZE];
  char reply[BUFFER_SIZE];
  int end_connection = 0;
  int getting_continuously = 0;

  // setting the timeout
  struct timeval tv = {controller.display_timeout_value, 0};
  setsockopt(socket, SOL_SOCKET, SO_RCVTIMEO, (struct timeval *)&tv, sizeof(struct timeval));


  int id = -1; // the id of the view associated to this thread
  pthread_t thread_id = pthread_self();

  fprintf(server_log, "Socket opened in thread %d\n", (int)thread_id);
  int size = recv(socket, client_message, BUFFER_SIZE, 0);
  while (size != 0) {
    client_message[size] = '\0';
    fprintf(server_log, "Received [%s] from thread %d\n", client_message, (int)thread_id);

    // i'm not proud of this but whatever
    char copy[BUFFER_SIZE];
    strcpy(copy, client_message);
    if (strcmp("getFishesContinuously", strtok(copy, " ")) == 0) {
      getting_continuously = 1;
    }

    if (size <= 0 && !getting_continuously) {
      fprintf(server_log, "[N%d]: disconnected by timeout\n", id);
      snprintf(reply, BUFFER_SIZE, "bye$");
      send(socket, reply, strlen(reply), 0);
      close(socket);
      a->views[id].taken = 0;
      pthread_exit(NULL);
    }

    handle_message(client_message, size, reply, &id, socket);
    fprintf(server_log, "Sent [%s] to thread %d\n", reply, (int)thread_id);
    strcat(reply, "$\0");
    send(socket,reply,strlen(reply),0);
    if (strcmp(reply, "bye$") == 0) {
      close(socket);
      a->views[id].taken = 0;
      pthread_exit(NULL);
    }

    size = recv(socket, client_message, BUFFER_SIZE, 0);
  }

  fprintf(server_log, "[N%d]: exiting socket thread\n", id);
  if (id != -1) {
    a->views[id].taken = 0;
  }
  close(socket);
  pthread_exit(NULL);
}

/* updates the fishes positions at each 1s */
void *timer_thread(void *arg) {

  while (1) {
    sleep(1);
    decrease_time();
  }
  pthread_exit(NULL);
}

int main(){

  int sockfd, client_socket;
  struct sockaddr_in server_addr, cli;
  socklen_t addr_size;


  if (start_log() == -1) {
    return -1;
  }

  // thread to receive input directly at the server
  pthread_t server_prompt;
  if (pthread_create(&server_prompt, NULL, prompt_thread, NULL) != 0 ) {
    printf("Failed to create prompt thread\n");
    exit(-1);
  }
  fprintf(server_log, "Prompt thread created\n");


  read_conf();

  // create
  sockfd = socket(PF_INET, SOCK_STREAM, 0);

  if (sockfd == -1) {
    printf("Error creating socket\n");
    exit(-1);
  }
  else {
    fprintf(server_log, "Socket created successfully\n");
  }

  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(controller.port);
  server_addr.sin_addr.s_addr = inet_addr(SERVER_ADDRESS);
  memset(server_addr.sin_zero, '\0', sizeof server_addr.sin_zero);


  // bind
  if (bind(sockfd, (struct sockaddr *) &server_addr, sizeof(server_addr)) != 0) {
    printf("Error %d while binding\n", errno);
    exit(-1);
  }
  else {
    fprintf(server_log, "Binding successfull\n");
  }

  // listen

  if (listen(sockfd, THREADS) == 0) {
    fprintf(server_log, "Listening\n");
  }
  else {
    printf("Error listening\n");
    exit(-1);
  }

  pthread_t tid[THREADS];
  int i = 0;


  pthread_t timer_prompt;
  if (pthread_create(&timer_prompt, NULL, timer_thread, NULL) != 0 ) {
    printf("Failed to create timer thread\n");
    exit(-1);
  }
  fprintf(server_log, "Timer thread created\n");

  // accept
  while(1) {

    addr_size = sizeof cli;
    client_socket = accept(sockfd, (struct sockaddr *) &cli, &addr_size);
    if (pthread_create(&tid[i], NULL, socket_thread, &client_socket) != 0 ) {
      printf("Failed to create thread\n");
      exit(-1);
    }

    if (i >= THREADS) {
      i = 0;
      while (i < THREADS) {
	pthread_join(tid[i++], NULL);
      }
      i = 0;
    }
  }
  return 0;
}

#include "pipe_networking.h"


/*=========================
  server_handshake
  args: int * to_client

  Performs the client side pipe 3 way handshake.
  Sets *to_client to the file descriptor to the downstream pipe.

  returns the file descriptor for the upstream pipe.
  =========================*/
int server_handshake(int *to_client) {
    puts("Server establishing connection to client");
    int wkp = open("Gandalf",O_RDONLY);
    if(!wkp){
        puts("Failure in opening well known pipe, make sure pipe exists");
        exit(0);
    }
    char pid[10];
    if(!read(wkp,pid,HANDSHAKE_BUFFER_SIZE)){
        puts("Failure in reading from pipe, make sure pipe exists");
        exit(-1);
    }
    puts("Server recieved private pipe name");
    *to_client = open(pid,O_WRONLY);
    if(!*to_client){
        puts("Failure in opening private pipe, make sure pipe exists");
        exit(-1);
    }
    close(wkp);
    sprintf(pid,"%d",getpid());
    mkfifo(pid,0644);
    puts("Connection established 1");
    if(!write(*to_client,pid,HANDSHAKE_BUFFER_SIZE)){
        puts("Failure in writing to private pipe, make sure pipe exists");
        exit(-1);
    }
    puts("Opening server private pipe");
    int upstream = open(pid,O_RDONLY);
    if(!upstream){
        puts("Failure in opening server private pipe, make sure pipe exists");
        exit(-1);
    }
    puts("Acknowledge having recieved the connection");
    return upstream;
}


/*=========================
  client_handshake
  args: int * to_server

  Performs the client side pipe 3 way handshake.
  Sets *to_server to the file descriptor for the upstream pipe.

  returns the file descriptor for the downstream pipe.
  =========================*/
int client_handshake(int *to_server) {
    char pid[10];
    sprintf(pid,"%d",getpid());
    mkfifo(pid,0644);
    int wrfd = open("Gandalf",O_WRONLY);
    if(!wrfd){
        puts("Failure in opening WKP client side");
        exit(-1);
    }
    puts("Client giving private pipe name to server");
    if(!write(wrfd,pid,HANDSHAKE_BUFFER_SIZE)){
        puts("Failure in writing to WKP client side");
        exit(-1);
    }
    puts("Client establishing a connection with server");
    int downstream = open(pid,O_RDONLY);
    if(!downstream){
        puts("Failure in opening private pipe client side");
        exit(-1);
    }
    puts("Connection established");
    char ackwait[10];
    if(!read(downstream,ackwait,HANDSHAKE_BUFFER_SIZE)){
        puts("Failure in opening private pipe client side");
        exit(-1);
    }
    puts("Client recieved server private pipe");
    *to_server = open(ackwait,O_WRONLY);
    if(!*to_server){
        puts("Failure in opening private pipe client side");
        exit(-1);
    }
    return downstream;
}

// Author: Jonathan Parlett
// Program Name: echofileserver.c
// Created: 2022-February-14
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <arpa/inet.h>
		
#define ll long long int
#define ull unsigned long long int
#define li long int
#define ui unsigned int

#define MAX 8192

int openListnerFd( struct sockaddr_in* server, int port);
void echo(int connfd, char ip[]);//takes a network connection fd as a an arg and echos input until connection closes
void echofile(int connfd, char ip[]);//takes a network connection fd as a an arg and awaits a file name from the client, echoing file once received

int listenfd, connfd, port; //listener and connection file descriptors, and the port
char eof = EOF;
struct sockaddr_in server, client; //client server ip info

void die(char s[]){
  printf("Error: %s\n", s);
  exit(1);
}

int main(int argc, char* argv[]){


  if( argc != 2){
    printf("Error: expected %s <port>\n", argv[0]);
    exit(1);
  }

  port = atoi(argv[1]); //port -> int

  listenfd = openListnerFd(&server, port);


  while(1){ //infinite loop to handle requests

    unsigned int clen = sizeof(client); //length of client ip struct 

    if( (connfd = accept(listenfd, (struct sockaddr*)&client, &clen)) < 0) //accept takes a pointer to size for some reason
      die("can't accept connection");

    char *client_ip = inet_ntoa(client.sin_addr);
    printf("Accepted new connection from a client %s:%d\n", client_ip, ntohs(client.sin_port));


    //now connfd is a bidirectional network connection

    // run echo service
    // if( fork() == 0){
      // echo(connfd, client_ip);
      // close(connfd);
      // exit(0);
    // }
    //run echofile service
    if( fork() == 0){
      echofile(connfd, client_ip);
      close(connfd);
      exit(0);
    }
  }

}

int openListnerFd( struct sockaddr_in* server, int port){

  listenfd = socket(AF_INET, SOCK_STREAM, 0);

  server -> sin_family = AF_INET; //IPV4

  server -> sin_addr.s_addr = INADDR_ANY;

  server -> sin_port = htons(port); //convert to network byte order

  if( bind(listenfd, (struct sockaddr*)server, sizeof(*server)) != 0)
    die("can't bind");

  if(listen(listenfd,10) != 0)
    die("can't listen");

  return listenfd;
}

void echo(int connfd, char ip[]){//takes a network connection fd as a an arg and echos input until connection closes
  
    char buf[MAX];

    ui nbytes = 0;

    while(1){//echo loop
    
       if( (nbytes = read(connfd, buf, MAX) ) < 0)
         die("couldn't read from connection");

       printf("received %d bytes from %s\n", nbytes, ip);

       if( write(connfd, buf, nbytes) < 0)
         die("couldn't write to connection");

       //write EOF
       if( write(connfd, &eof, 1) < 0)
         die("couldn't write EOF");
    }

}

void echofile(int connfd, char ip[]){//takes a network connection fd as a an arg and awaits a file name from the client, echoing file once received

    char buf[MAX];

    ui nbytes = 0;

    char *prompt = "$ enter another file: ";

    while(1){//echo loop
    
       if( (nbytes = read(connfd, buf, MAX) ) < 0)
         die("couldn't read from connection");

       printf("received %d bytes from %s\n", nbytes, ip);

       buf[nbytes-1]='\0'; //cut newline

       FILE* fp = fopen(buf, "r");

       char line[MAX];
       while(fgets(line, MAX, fp) != NULL){
         if( write(connfd, line, strlen(line)) < 0)
           die("couldn't write to connection");
       }

       if( write(connfd, prompt, strlen(prompt)) < 0 )
         die("couldn't write prompt");
    
       //write EOF
       if( write(connfd, &eof, 1) < 0)
         die("couldn't write EOF");

       printf("Echoed File\n");
    }

}

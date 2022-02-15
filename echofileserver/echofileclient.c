// Author: Jonathan Parlett
// Program Name: echofileserver.c
// Created: 2022-February-14
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <strings.h>
#include <netdb.h>
		
#define ll long long int
#define ull unsigned long long int
#define li long int
#define ui unsigned int

#define MAX 8192
#include <stdlib.h>
#include <arpa/inet.h>

void die(char s[]){
  printf("Error: %s\n", s);
  exit(1);
}


int readline(int fd, char buf[], int bufsize);

int main(int argc, char* argv[]){


  if( argc != 3){
    printf("Error: expected %s <server ip> <port>\n", argv[0]);
    exit(1);
  }

  struct sockaddr_in server;

  struct hostent *hp; //store info for host lookup, used by gethostbyname()

  char *serverIp = argv[1];

  int port = atoi(argv[2]);

  int connfd;

  printf("server: %s   port: %d\n", serverIp, port);

  if( (connfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    die("could not create socket"); // bidirectional connection

  hp = gethostbyname(serverIp);

  server.sin_family = AF_INET; //IPV4

  // server.sin_addr.s_addr = inet_addr(serverIp); //convert given addr
  bcopy((char *)hp->h_addr_list[0], (char *)&server.sin_addr.s_addr, hp->h_length); //grab required address, doing it this way allows us to handle hostnames or ips since gethostbyname is indifferent

  server.sin_port = htons(port); //convert to network byte order

  // attempt to open connection
  if( connect(connfd, (struct sockaddr*)&server, sizeof(server)) != 0)
    die("could not open connection");

  printf("Sucessfully connected!!\n");

  char buf[MAX];

  int nbytes;

  while(1){//main loop

    //read stdin, write to connection
    nbytes = read(STDIN_FILENO, buf, MAX); 

    printf("read from stdin: %s\n", buf);

    write(connfd, buf, nbytes);

    //read from connection until connection is quiet
    char c;
    while( read(connfd, &c, 1) > 0){
      if( c == EOF) break;
      write(STDOUT_FILENO, &c, 1);
    }
  }

}

int readline(int fd, char buf[], int bufsize){

  int i=0;

  while( read(fd, (buf+i), 1) > 0 && i < bufsize ){
    if(buf[i]=='\n') break;
  }

  buf[i+1]='\0'; //delim

  return i+1; //len of str
}
 




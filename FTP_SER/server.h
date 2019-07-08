#ifndef SERVER_H
#define SERVER_H
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<assert.h>
#include<unistd.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<pthread.h>
#include<fcntl.h>
#include<mysql/mysql.h>
#include<iostream>
#include"my_sql.h"
using namespace std;
void *thread_fun(void *arg);
class Mysql;
class Server
{
public:
	Server();
	//Mysql mysql;
	void server_start(Mysql mysql);
	void receive_file(char *myargv[],int c);
	void thread_receive_file(char *myargv[],int c);
	void send_file(char *myargv[],int c);
	int getsocket();
	int socket_create();
	void handle_message(int sockfd);
	void list(char *myargv[],int c);
	
private:
	int sockfd;

	//class Mysql;

};
#endif

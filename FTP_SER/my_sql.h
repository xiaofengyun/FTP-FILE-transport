#ifndef MYSQL_H
#define MYSQL_H
#include<iostream>
#include<mysql/mysql.h>
#include<string.h>
#include<stdio.h>
#include<errno.h>
#include<stdlib.h>
#include<dirent.h>
using namespace std;
class Mysql
{
public:
	Mysql();
	//~Mysql();
	void add(long int size,char *name);
	//void del();
	//void find();
	void check_file();

	MYSQL *mpcon;
	MYSQL_RES *mp_res;
	MYSQL_ROW  mp_row;
};

#endif

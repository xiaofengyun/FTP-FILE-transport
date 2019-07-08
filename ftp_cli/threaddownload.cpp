#include"threaddownload.h"
#include<string>
#include<stdio.h>
#include <QDebug>
#include<QFile>
#include<QTcpServer>
#include"mainwindow.h"


threadDown::threadDown(char sendbuff[],int i)
{
    strcpy(buff,sendbuff);
    qDebug()<<"线程初始化";
    qDebug()<<buff;
    a =i;
}



void threadDown::run()
{

    int i=a;

    emit thread_to_main(buff,i);

}

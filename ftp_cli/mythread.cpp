#include"mythread.h"
#include <QDebug>
#include<QFile>
#include<QTcpServer>
#include"mainwindow.h"
mythread::mythread(QString dir,QString data,QString ip,QString port)
{
    morename =data;
    ip2=ip;
    port2=port;
    dir2 =dir;


}
void mythread::read_thread()
{
    qDebug()<<"start recv...";

    QString s =sockfddown->readAll();
    qDebug()<<s;
    //fp->close();
}
void mythread::run()
{
    QString fileName ="/"+morename;
    QString lu =dir2+fileName;
    qDebug()<<lu;
    fp = new QFile(dir2+"/"+fileName);

    if(!fp->open(QIODevice::WriteOnly))
    {
        qDebug()<<"open file fail...";
    }

    if ( fp->exists())
    {
        qDebug()<<"file have create exist...";


    }

    sockfddown =new QTcpSocket();//创建套接字
    char *str1;
    int str2=port2.toInt();
    QByteArray ba =ip2.toLatin1();
    str1 =ba.data();
    sockfddown->connectToHost(str1,str2);
    if(!sockfddown->waitForConnected(30000))
    {
        qDebug()<<("线程连接失败");
    }
    else
    {
        qDebug()<<("线程连接成功");
        QFile file(morename);
        if ( file.exists())
        {
                //return ;
            qDebug()<<"file open success...";
        }
        file.open( QIODevice::ReadWrite | QIODevice::WriteOnly );
       // file.close();
       QString send ="download "+morename;
       char*  ch;
       QByteArray ba = send.toLatin1(); // must
       ch=ba.data();
       qDebug()<<ch;
       sockfddown->write(ch);//发送下载请求
       sockfddown->flush();

       int num;
       int num2=0;

       while(sockfddown->waitForReadyRead(10))
        {

            QByteArray buff  = sockfddown->readAll();
            if(strncmp(buff,"ok#",3)==0)
            {
                char *bu;
                bu=buff.data();
                int totalsize = 0;
                sscanf(bu+3,"%d",&totalsize);//获得大小
                qDebug()<<totalsize;
                num=totalsize;

                //emit notify_creat(num);
                sockfddown->write("ok");

            }
            else
            {

                 num2+=buff.size();
                 //emit notify_value(num2);
                 qDebug()<<buff;
                 fp->write(buff);

             }

        }
       qDebug()<<"size ="<<fp->size();
       if(fp->size()==num)
       {
           emit if_download();
       }
       fp->close();



    }

}

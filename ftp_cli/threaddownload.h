#ifndef THREADDOWNLOAD
#define THREADDOWNLOAD
#include<QMutex>
#include<QThread>
#include<QTcpServer>
#include<QFile>
#include <QMainWindow>
#include<QProgressDialog>
#include <QWidget>
#include<QTimer>

class threadDown:public QThread
{
    Q_OBJECT

public:

    QFile *fp;

    threadDown(char sendbuff[],int i);
    void run();//
signals:
    void thread_to_main(char *buff,int i);



private:
    char buff[1024];
    int a;

    QProgressDialog *pd;

};

#endif // THREADDOWNLOAD


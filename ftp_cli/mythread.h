#ifndef MYTHREAD
#define MYTHREAD
#include<QThread>
#include<QTcpServer>
#include<QFile>
#include <QMainWindow>
#include<QProgressDialog>
#include <QWidget>
#include<QTimer>

class mythread:public QThread
{
    Q_OBJECT

public:
    QTcpSocket *sockfddown;
    QFile *fp;

    mythread(QString dir,QString data,QString ip,QString port);
    void run();//
signals:
    void notify_creat(int max);
    void notify_value(int i);
    void if_download();
public slots:
     void read_thread();
private:
    QString morename;
    QString ip2;
    QString port2;
    QString dir2;
    QProgressDialog *pd;

};
#endif // MYTHREAD


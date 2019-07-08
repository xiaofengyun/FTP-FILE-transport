#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include<QTcpSocket>
#include<QWidget>
#include"dialog.h"
#include<QTcpServer>
#include<QFile>
#include"dialogupload.h"
#include"download.h"
#include<QByteArray>
#include"mythread.h"
#include<QProgressDialog>
#include"threaddownload.h"
#include<stdio.h>
#include<QMutex>
#include <QMetaType>
class mythread;
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    //qRegisterMetaType<char *>( "char *" );
    int pro_value;//进度条值
    int size_int=0;//上传时记录的文件总大小

    QMutex mutex;

    QProgressDialog *progressDlg;
    int thread_sum=0;
    int success_num=0;
    QTcpSocket *sockfd;
    QString ip;
    QString port;


    explicit MainWindow(QWidget *parent = 0);
    void no_click();
    void thread_upload();
    ~MainWindow();
signals:
    void ll();

private slots:

    void start_to_up(char *buff,int i);//上传线程信号函数
    void creat_progress(int max);
    void set_value(int i);
    void if_success();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_lineEdit_editingFinished();

    //void on_lineEdit_2_returnPressed();

    void on_pushButton_4_clicked();

    void on_pushButton_3_clicked();

    void on_lineEdit_2_editingFinished();


    void readmsg();
    void readmsg_up();
    void start_to_send(QString filename);
    void receiveData(QString data);

    void on_pushButton_5_clicked();

private:
    Ui::MainWindow *ui;
    QString mString;
    QString mString2;
    Dialog *dialog;
    download *load;
    Dialogupload *dialogupload;

    
    Dialog dia;//list按钮的子窗口


};

#endif // MAINWINDOW_H

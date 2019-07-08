#include "mainwindow.h"
#include "ui_mainwindow.h"
#include"ip_port.h"
#include<QDebug>
#include<QMessageBox>
#include"dialog.h"
#include"dialogupload.h"
#include<QFileDialog>
#include<time.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    on_lineEdit_editingFinished();
    on_lineEdit_2_editingFinished();

}
void MainWindow::creat_progress(int max)
{
     qDebug()<<"max="<<max;

}
void MainWindow::set_value(int i)
{
    qDebug()<<"i="<<i;

}

void MainWindow::start_to_up(char *sendbuff,int i)//上传线程调用操函数
{

    mutex.lock();//加锁
    int len =strlen(sendbuff)-3;
    pro_value+=(strlen(sendbuff)-2);
    qDebug()<<"len="<<len;
    qDebug()<<"pro_value="<<pro_value;
   // progressDlg->setValue(len);


    QString tmp1;
    tmp1.sprintf("线程：%d 开始发送...",i);

    qDebug()<<tmp1;
    ui->textBrowser->append(tmp1);
    sockfd->write(sendbuff);

    QString tmp2;
    tmp2.sprintf("线程：%d 发送完毕...",i);
    qDebug()<<tmp2;
    ui->textBrowser->append(tmp2);

    mutex.unlock();//解锁
    if(pro_value==size_int)
    {
        QMessageBox::about(this, "About", "文件上传完成！");


        progressDlg->close();

    }
}

void MainWindow::if_success()
{
    success_num++;
    qDebug()<<"num="<<success_num;
    qDebug()<<"thread_sum="<<thread_sum;
    if(success_num==thread_sum)
    {
        QMessageBox::about(this, "About", "所有文件下载完成！");
        success_num=0;
    }
}
MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_lineEdit_editingFinished()//输入ip
{
     ip = ui->lineEdit->text();
    ui->textBrowser->setText(ip);
    ui->lineEdit->setText(ip);

}

void MainWindow::on_lineEdit_2_editingFinished()//输入port
{
     port = ui->lineEdit_2->text();
     ui->textBrowser->append(port);

}

void MainWindow::on_pushButton_4_clicked()//点击按钮进行连接connect
{
    qDebug()<<ip;
    qDebug()<<port;
    if(!if_is_ip(ip)||!if_is_port(port))
    {
        QMessageBox::about(this, "About", "请输入正确ip或者port！");
    }
    sockfd =new QTcpSocket();//创建套接字

    char *str1;
    int str2=port.toInt();
    QByteArray ba =ip.toLatin1();
    str1 =ba.data();
    sockfd->connectToHost(str1,str2);
    if(!sockfd->waitForConnected(30000))
    {
        qDebug()<<("连接失败");
         ui->textBrowser->append("连接服务器失败");
    }
    else
    {
        qDebug()<<("连接成功");
         ui->textBrowser->append("连接服务器成功");
    }


}
void MainWindow::readmsg()
{
    char buff[1024];
    sockfd->read(buff,1024);
    if(strncmp(buff,"ok#",3)==0)
    {
        qDebug()<<"recv success...";
       // qDebug()<<buff+3;
    }
    else
    {

        qDebug()<<"recv error";
    }
    qDebug()<<buff+3;

    dialog->show_list(buff);



}
void MainWindow::on_pushButton_3_clicked()//list
{
        dialog =new Dialog(this);//构造子窗口
        dialog->setModal(false);

        char *str ="ls";
        sockfd->write(str);
        char buf[1024];//接收

       // connect(sockfd,SIGNAL(readyRead()),this,SLOT(readmsg()));
        if(sockfd->waitForReadyRead(10))
         {


             QByteArray recvbuff  = sockfd->readAll();
             qDebug()<<recvbuff;
             char *buff =recvbuff.data();
             if(strncmp(buff,"ok#",3)==0)
             {
                 qDebug()<<"recv success...";
                 qDebug()<<buff+3;
                 dialog->show_list(buff);
             }
             else
             {

                 qDebug()<<"recv error";
             }

         }

        dialog->show();
}

void MainWindow::start_to_send(QString filename)
{


}

void MainWindow::readmsg_up()
{
    char buff[1024];

    sockfd->read(buff,1023);
    qDebug()<<buff+3;
    char opbuff[256]={0};

    QString str=QString(QLatin1String(buff+3));
    qDebug()<<str;

    if(strncmp(buff,"ok",2)==0)
    {
        qDebug()<<"recv success...";
        qDebug()<<"start to send file...";
        /*开始发送*/
       // int n=0;
        QFile * m_localFile;
         m_localFile = new QFile(str);//类似一个文件指针
        if( !m_localFile->open(QFile::ReadOnly))
        {
            qDebug()<<"open file error!";
            return;
        }
        //打开成功
        qDebug()<<"打开文件成功！";
        qint64 n=0;
        char buff[256]={0};
        QByteArray b;
        while((n=m_localFile->read(buff,255))>0)
        {
            b=buff;
            sockfd->write(b);
        }
        qDebug()<<"put finish";
        sockfd->flush();
    }
    else
    {

        qDebug()<<"recv error";
    }

}
void MainWindow::on_pushButton_clicked()//upload
{
    thread_upload();
    /*
    qDebug()<<"ok";
    qint64 m_totalBytes;
    QFile * m_localFile;

    //dialogupload =new Dialogupload(this);//构造子窗口
   // dialogupload->setModal(false);
    QString path = QFileDialog::getOpenFileName(this,"Open a file","/","files (*)");
    QFileInfo info(path);

    QString upload="选择上传文件："+path;
    ui->textBrowser->append(upload);
    m_localFile = new QFile(path);//类似一个文件指针
    if( !m_localFile->open(QFile::ReadOnly))
    {
        qDebug()<<"open file error!";
        return;
    }
    //打开成功
    qDebug()<<"打开文件成功！";

    m_totalBytes = m_localFile->size();//得到文件总大小
    qDebug()<<"文件大小："<<m_localFile->size();
    QString up="upload";
    QString size =QString::number(m_totalBytes, 10);
    up+=" "+path+" "+info.fileName()+" "+size;

    char*  ch;
    QByteArray ba = up.toLatin1(); // must
    ch=ba.data();
    qDebug()<<ch;
    qDebug()<<sockfd;
    sockfd->write(ch);//发送上传请求
    sockfd->flush();


    connect(sockfd,SIGNAL(readyRead()),this,SLOT(readmsg_up()));
  //  dialogupload->show();
*/

}


void MainWindow::receiveData(QString data)

{
    ui->textBrowser->append("选择了下载文件：");
    ui->textBrowser->append(data);
    /*选择保存路径*/
    QString dir = QFileDialog::getExistingDirectory(this, "Open Directory",
                                                       "/",QFileDialog::ShowDirsOnly );
    QStringList list = data.split(" ");//QString字符串分割函数
    mythread *thread[10];
    thread_sum =list.size();
    for(int i=0;i<list.size();i++)
    {
       thread[i] = new mythread(dir,list.at(i),ip,port); //新建线程对象
       thread[i]->start();  //启动线程
       //thread[i]->wait();
       connect(thread[i],SIGNAL(notify_creat(int)),this,SLOT(creat_progress(int)));
       connect(thread[i],SIGNAL(notify_value(int)),this,SLOT(set_value(int)));
       connect(thread[i],SIGNAL(if_download()),this,SLOT(if_success()));


    }
    //start_to_reveive(data,ip,port);


    for(int j=0;j<list.size();j++)
    {
        thread[j]->wait();
    }



}

void MainWindow::on_pushButton_2_clicked()//download
{
    qDebug()<<"start to download...";

    load =new download(this);
    load->setModal(true);
    connect(load,SIGNAL(sendData(QString)),this,SLOT(receiveData(QString)));



    load->show();

}


void MainWindow::thread_upload()/////////////多线程上传
{
    qDebug()<<"start thread upload...";
    qint64 m_totalBytes;
    QFile * m_localFile;


    QString path = QFileDialog::getOpenFileName(this,"Open a file","/","files (*)");
    QFileInfo info(path);//path就是打开文件的路径

    QString upload="选择上传文件："+path;
    ui->textBrowser->append(upload);
    m_localFile = new QFile(path);//类似一个文件指针
    if( !m_localFile->open(QFile::ReadOnly))
    {
        qDebug()<<"open file error!";
        return;
    }
    //打开成功
    qDebug()<<"打开文件成功！";

    m_totalBytes = m_localFile->size();//得到文件总大小
    QString size =QString::number(m_totalBytes, 10);
    qDebug()<<"文件大小："<<m_localFile->size();
    QString up="upload";
    up+=" "+info.fileName()+" "+size;

    char*  ch;
    QByteArray ba = up.toLatin1(); // must
    ch=ba.data();
    sockfd->write(ch);

    if(sockfd->waitForReadyRead(10))
     {

         QByteArray buff  = sockfd->readAll();
         qDebug()<<buff;
         if(strncmp(buff,"ok",2)!=0)
         {
             qDebug()<<"server no message...";
             return;
         }


        int n=0;
        int i=0;
        threadDown *thread[10];
        char sendbuff[1024]={0};
        size_int =size.toInt();
        qDebug()<<"size="<<size_int;
        int num_thread=size_int/1000;
        if(size_int-num_thread*1000>0)
        {
            num_thread++;
        }
        qDebug()<<"thread="<<num_thread;
        qRegisterMetaType<char *>( "char *" );
        qDebug()<<"size="<<size_int;

        progressDlg=new QProgressDialog( QStringLiteral("上传完成......"), QStringLiteral("取消"),0,size_int,this);

        progressDlg->setWindowModality(Qt::WindowModal);

        progressDlg->setWindowTitle(QStringLiteral("请稍候"));
        progressDlg->setMinimumDuration(0);
        pro_value =0;



      //  progressDlg->setValue(109);
        progressDlg->show();

        for(;i<num_thread;i++)
        {
            qDebug()<<"i="<<i;

            if(i<=9)
            {
                sprintf(sendbuff,"%d",i);
                sprintf(sendbuff+1,"%s",NULL);
            }
            else
            {
                sprintf(sendbuff,"%d",i);
            }
            qDebug()<<sendbuff[0];
            qDebug()<<sendbuff[1];
            qDebug()<<"sendbuff="<<sendbuff;



            n=m_localFile->read(sendbuff+2,1000);
            qDebug()<<sendbuff;
            qDebug()<<strlen(sendbuff);

            thread[i] = new threadDown(sendbuff,i); //新建线程对象
            thread[i]->start();  //启动线程

            bool b =connect(thread[i],SIGNAL(thread_to_main(char *,int)),this,SLOT(start_to_up(char *,int)));
            qDebug()<<"b="<<b;
            thread[i]->wait();
            memset(sendbuff,0,sizeof(sendbuff));
            qDebug()<<"------------------------------------------------------------";


        }
       /* while((n=m_localFile->read(sendbuff,1000))>0)
        {
            qDebug()<<sendbuff;
            int len =strlen(sendbuff);

            char xulie[32]={0};
            sprintf(xulie,"#%d",i);
            strcat(sendbuff,xulie);//拼接buff+序列
            qDebug()<<sendbuff;
            thread[i] = new threadDown(sendbuff); //新建线程对象
            thread[i]->start();  //启动线程
            thread[i]->wait();

            bool b =connect(thread[i],SIGNAL(thread_to_main(char *)),this,SLOT(start_to_up(char *)));
            qDebug()<<"b="<<b;
            i++;
            qDebug()<<"i="<<i;
        }
        for(int j=0;j<i;i++)
        {
           // thread[j]->wait();
        }*/
    }


}


void MainWindow::on_pushButton_5_clicked()
{
    qDebug()<<"start many file...";
    qint64 m_totalBytes;
    QFile * m_localFile;


    QString strs;
    QStringList file_list, output_name;
    QStringList str_path_list = QFileDialog::getOpenFileNames(this, tr("选择转码文件"), tr("/home"), tr("视频文件(*.mp4 *.m3u8);;所有文件（*.*);;"));
        for (int i = 0; i < str_path_list.size(); i++){
            QString str_path = str_path_list[i];
            //单个文件路径
            qDebug() << "path=" << str_path;
            QFileInfo file = QFileInfo(str_path);
            //获得文件名
            QString file_name = file.fileName();
            file_list.append(str_path);
            output_name.append(file_name);
            strs.append(file_name);
            strs += "\n";
        }

     qDebug()<<"===";

     qDebug()<<strs;
















}

#include "dialogupload.h"
#include "ui_dialogupload.h"

Dialogupload::Dialogupload(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialogupload)
{
    ui->setupUi(this);
    m_payloadSize = 64*1024;//每次发送64kb
    m_totalBytes = 0;
    m_bytesToWrite = 0;
    m_bytesWritten = 0;
}

Dialogupload::~Dialogupload()
{
    delete ui;
}
/*
void Dialogupload::start_to_send(QString filename)
{
     m_localFile = new QFile(filename);//类似一个文件指针
     if( !m_localFile->open(QFile::ReadOnly))
     {
         qDebug()<<"open file error!";
         return;
     }
     //打开成功
     qDebug()<<"打开文件成功！";

     m_totalBytes = m_localFile->size();//得到文件总大小
     qDebug()<<"文件大小："<<m_localFile->size();
     qDebug()<<"m_totalBytes(总大小):="<<m_totalBytes;
     qDebug()<<"m_bytesWritten(已发送):="<<m_bytesWritten;
     qDebug()<<"m_bytesToWrite(还剩):="<<m_bytesToWrite;



}

*/
QString Dialogupload::on_pushButton_clicked()
{
    /*QString filename = QFileDialog::getOpenFileName(this,"Open a file","/","files (*)");
    ui.lineEdit_filename->setText(filename);
    return filename;
   /* 

*/

}


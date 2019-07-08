#ifndef DIALOGUPLOAD_H
#define DIALOGUPLOAD_H
#include<QFile>

#include <QDialog>

namespace Ui {
class Dialogupload;
}

class Dialogupload : public QDialog
{
    Q_OBJECT

public:
    explicit Dialogupload(QWidget *parent = 0);
   // void readmsg_up(QString filename);
    //void start_to_send();
    ~Dialogupload();

private slots:
    QString on_pushButton_clicked();

private:
    QFile *m_localFile;//要发送的文件
    qint64 m_totalBytes;//发送数据快总大小
    qint64 m_payloadSize ;//每次发送64kb
    //qint64  m_totalBytes ;
    qint64    m_bytesToWrite ;
    qint64    m_bytesWritten ;

    Ui::Dialogupload *ui;
};

#endif // DIALOGUPLOAD_H

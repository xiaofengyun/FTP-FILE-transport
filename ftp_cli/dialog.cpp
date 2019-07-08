#include "dialog.h"
#include "ui_dialog.h"
#include<QDebug>
Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui2(new Ui::Dialog)
{
   // this->setObjectName("dialog");    //这句话一定要有，不然，整个界面上的控件背景都跟界面背景一样
    //this->setStyleSheet("QDialog#dialog{border-image:url(:/image/C:/Users/wangyu23/Desktop/79a88190fbb8aaed0c50f4afe7d7ff4f.jpg)}");
    ui2->setupUi(this);
   // ui2->textBrowser->setText("pppppp");
}

Dialog::~Dialog()
{
    delete ui2;
}
//Ui::Dialog *getui();
void Dialog::show_list(char buff[])
{
    qDebug()<<"dialog";
   // ui2->textBrowser->setTextColor(QColor(100, 184, 255));
    ui2->textBrowser->setText("文件清单如下：");
    ui2->textBrowser->append(buff+3);

}

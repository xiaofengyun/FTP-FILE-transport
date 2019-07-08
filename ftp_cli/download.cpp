#include "download.h"
#include "ui_download.h"

download::download(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::download)
{
    ui->setupUi(this);
}

download::~download()
{
    delete ui;
}

void download::on_buttonBox_accepted()
{
    emit sendData(ui->lineEdit->text());
}

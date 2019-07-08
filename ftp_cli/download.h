#ifndef DOWNLOAD_H
#define DOWNLOAD_H

#include <QDialog>

namespace Ui {
class download;
}

class download : public QDialog
{
    Q_OBJECT

public:
    explicit download(QWidget *parent = 0);
    ~download();
signals:
    void sendData(QString );
private slots:
    void on_buttonBox_accepted();

private:
    Ui::download *ui;
};

#endif // DOWNLOAD_H

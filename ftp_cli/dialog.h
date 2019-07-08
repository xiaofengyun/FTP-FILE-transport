#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    void show_list(char buff[]);
     Ui::Dialog *getui();
    ~Dialog();
private:

    Ui::Dialog *ui2;
};

#endif // DIALOG_H

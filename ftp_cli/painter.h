#ifndef PAINTER
#define PAINTER
#include<QWidget>
#include<QObject>
#include <QPainter>
#include <QPen>
class PaintedWidget:public QWidget
{
    Q_OBJECT
public:
    PaintedWidget(QWidget *parent =0);
protected:
    void paintEvent(QPaintEvent *);
};

#endif // PAINTER


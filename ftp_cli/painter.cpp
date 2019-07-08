#include"painter.h"
#include"mainwindow.h"
#include<QDebug>


PaintedWidget::PaintedWidget(QWidget *parent):QWidget(parent)
{
    resize(800,600);
    setWindowTitle(tr("paint demo"));
}

void PaintedWidget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.drawLine(80,100,650,500);
    painter.setPen(Qt::red);
    painter.drawRect(10,10,100,400);
    painter.setPen(QPen(Qt::green, 5));
    painter.setBrush(Qt::blue);
    painter.drawEllipse(50, 150, 400, 200);
}

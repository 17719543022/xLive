#include "extendqlabel.h"
#include <QDebug>
#include <QPainter>

extendQLabel::extendQLabel(QWidget *parent)
    : QLabel(parent)
    , isMousePress(false)
{

}

void extendQLabel::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        isMousePress = true;

        begin = event->pos();
    }
}

void extendQLabel::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        end = event->pos();
        isMousePress = false;
        update();
    }
}

void extendQLabel::mouseMoveEvent(QMouseEvent *event)
{
    if (event->buttons() & Qt::LeftButton)
    {
        mid = event->pos();
        update();
    }
}

void extendQLabel::paintEvent(QPaintEvent *event)
{
    QLabel::paintEvent(event);

    QPainter painter(this);
    painter.setPen(QPen(Qt::red, 2));

    if (isMousePress)
    {
      painter.drawRect(QRect(begin, mid));
    } else {
      painter.drawRect(QRect(begin, end));
    }
}

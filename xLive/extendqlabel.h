#ifndef EXTENDQLABEL_H
#define EXTENDQLABEL_H

#include <QObject>
#include <QLabel>
#include <QMouseEvent>

class extendQLabel : public QLabel
{
    Q_OBJECT
public:
    extendQLabel(QWidget *parent=nullptr);

    void mousePressEvent(QMouseEvent *event) override;

    void mouseReleaseEvent(QMouseEvent *event) override;

    void mouseMoveEvent(QMouseEvent *ev) override;

    void paintEvent(QPaintEvent *event) override;

private:
    bool isMousePress;
    QPoint begin, end, mid;
};

#endif // EXTENDQLABEL_H

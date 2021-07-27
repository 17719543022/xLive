#ifndef EXTENDQLABEL_H
#define EXTENDQLABEL_H

#include <QObject>
#include <QLabel>
#include <QMouseEvent>
#include <QNetworkReply>
#include <QJsonArray>
#include <QMenu>
#include <QJsonDocument>
#include <QPainter>

class Frame {
public:
    Frame();
    void dump();
    QString currentPath;
    QPoint begin;
    QPoint end;
    QString value;
    int valueId;
    bool isValid;
};

class extendQLabel : public QLabel
{
    Q_OBJECT
public:
    extendQLabel(QWidget *parent=nullptr);

    void setCurrentPath(QString str);

    void mousePressEvent(QMouseEvent *event) override;

    void mouseReleaseEvent(QMouseEvent *event) override;

    void mouseMoveEvent(QMouseEvent *ev) override;

    void paintEvent(QPaintEvent *event) override;

    void contextMenuEvent(QContextMenuEvent *ev) override;

private slots:
    void on_Load();

    void on_LoadResponse(QNetworkReply* reply);

    void actionsSlot();

private:
    bool isMousePressed;
    QPoint begin, end, mid;
    QJsonDocument document;
    QJsonArray dictoryArray;
    QMenu *m_menu1;
    Frame frames[10];
    QString currentPath;
    QString value;
};

#endif // EXTENDQLABEL_H

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
    QString currentId;
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

    void setCurrentId(QString str);

    void setCurrentPixmap(QPixmap pixmap);

    void setCurrentWidth(int width);

    void setCurrentHeight(int height);

    void setRfid(QString str);

    void setFrames();

    bool isFramesExists();

    void mousePressEvent(QMouseEvent *event) override;

    void mouseReleaseEvent(QMouseEvent *event) override;

    void mouseMoveEvent(QMouseEvent *ev) override;

    void paintEvent(QPaintEvent *event) override;

    void contextMenuEvent(QContextMenuEvent *ev) override;

    void upLoad();

    void doDeleteFrame();

private slots:
    void on_Load();

    void on_LoadResponse(QNetworkReply *reply);

    void on_hazardousResponse(QNetworkReply *reply);

    void actionsSlot();

signals:
    void uploadFailed();

    void uploadSuccess(QString newPath);

    void deleteFrame();

private:
    bool isMousePressed;
    QPoint begin, end, mid;
    QPoint right;
    QJsonDocument document;
    QJsonArray dictoryArray;
    QMenu *m_menu1;
    Frame frames[10];
    QString currentPath;
    QString currentId;
    QPixmap currentPixmap;
    int currentWidth;
    int currentHeight;
    QString rfid;
    QString value;
    int valueId;
};

#endif // EXTENDQLABEL_H

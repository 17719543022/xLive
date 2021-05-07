#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "listener.h"
#include "QJsonObject"
#include "QJsonDocument"
#include <QJsonArray>
#include <QNetworkReply>
#include <QTableWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    QPixmap getQPixmapSync(QString str);

    void doSetPixmap();

    void fillTableTotally(QTableWidget *table, QJsonArray array);

private slots:
    void onNewSerialData(QString strRequest);

    void postResponse(QNetworkReply* reply);

    void on_pushButtonNImage_clicked();

    void on_cellClicked(int row, int column);

private:
    Ui::MainWindow *ui;
    Listener listener;
    QJsonDocument document;
    QJsonArray array;

    QString afterXPhotoPath;
    QString beforeXPhotoPath;
    bool isBeforeAfterChanged;
};

#endif // MAINWINDOW_H

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "listener.h"
#include "QJsonDocument"
#include <QJsonArray>
#include <QNetworkReply>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onNewSerialData(QString strRequest);

    void postResponse(QNetworkReply* reply);

private:
    Ui::MainWindow *ui;
    Listener listener;
    QJsonDocument document;
    QJsonArray array;
};
#endif // MAINWINDOW_H

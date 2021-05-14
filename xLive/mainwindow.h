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

    void doSetPixmap(QJsonArray array, int row);

    void fillRightTableTotally(QTableWidget *table, QJsonArray array);

    void fillBottomTableGradually();

private slots:
    void onNewSerialData(QString strRequest);

    void postResponse(QNetworkReply* reply);

    void on_pushButtonNImage_clicked();

    void on_rowClicked(int row, int column);

    void on_columnClicked(int row, int column);

private:
    Ui::MainWindow *ui;
    Listener listener;
    QJsonDocument document;
    QList<QJsonDocument> documents;
    int rowRight;
    bool isBeforeAfterChanged;
};

#endif // MAINWINDOW_H

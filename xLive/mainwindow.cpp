#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QDebug"
#include <QNetworkRequest>
#include <QNetworkAccessManager>
#include "settings.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setWindowFlag(Qt::FramelessWindowHint);

    // 开启HTTP服务StartHTTPServer
    int serverPort = LocalSettings::instance()->value("Device/serverPort").toInt();
    int nRet = StartHTTPServer(serverPort, &listener);
    if (nRet == 0) {
        qDebug() << "server strart port: " << serverPort;
    } else {
        qDebug() << "server fail";
    }

    connect(&listener, &Listener::newSerialData, this, &MainWindow::onNewSerialData);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::postResponse(QNetworkReply* reply)
{
    qDebug() << "reply: " << reply;
}

void MainWindow::onNewSerialData(QString strRequest)
{
    Q_UNUSED(strRequest)

    document = QJsonDocument();
    array = QJsonArray();

    QNetworkRequest request;
    QNetworkAccessManager* naManager = new QNetworkAccessManager(this);

    connect(naManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(postResponse(QNetworkReply*)));

    // Header
}

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QDebug"
#include <QNetworkRequest>
#include <QNetworkAccessManager>
#include <QUuid>
#include "settings.h"
#include "common.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , afterXPhotoPath(QString())
    , beforeXPhotoPath(QString())
    , isBeforeAfterChanged(false)
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

QPixmap MainWindow::getQPixmapSync(QString str)
{
    const QUrl url = QUrl::fromUserInput(str);

    QNetworkRequest request(url);
    QNetworkAccessManager *naManager = new QNetworkAccessManager(this);
    QNetworkReply* reply = naManager->get(request);

    QEventLoop eventLoop;
    connect(reply, &QNetworkReply::finished, &eventLoop, &QEventLoop::quit);
    eventLoop.exec(QEventLoop::ExcludeUserInputEvents);

    QByteArray byteArray = reply->readAll();

    QPixmap pixmap;
    pixmap.loadFromData(byteArray);

    return pixmap;
}

void MainWindow::postResponse(QNetworkReply* reply)
{
    QVariant status = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute);

    if (status.isValid()) {
        qDebug() << "status: " << status.toInt();
    }

    QVariant reason = reply->attribute(QNetworkRequest::HttpReasonPhraseAttribute);

    if (reason.isValid()) {
        qDebug() << "reason: " << reason.toString();
    }

    QNetworkReply::NetworkError err = reply->error();

    if (err != QNetworkReply::NoError) {
        qDebug() << "Failed: " << reply->errorString();
    } else {
        QByteArray all = reply->readAll();

        QJsonParseError err;
        document = QJsonDocument::fromJson(all, &err);

        if (err.error == QJsonParseError::NoError) {
            QJsonObject obj = document.object();

            qDebug() << "obj: " << obj;

            if (obj.contains("results")) {
                QJsonValue results = obj.value("results");
                if (results.isArray()) {
                    array = results.toArray();

                    if (array.size() > 0) {
                        ui->labelRightMeitouText_1->setText("RFID编号: " + array.at(0).toObject().value("rfid").toString());
                        ui->labelRightMeitouText_2->setText("行李框编号: " + array.at(0).toObject().value("boxNo").toString());

                        afterXPhotoPath = array.at(array.size() - 1).toObject().value("details").toObject().value("afterXPhotoPath").toString();
                        beforeXPhotoPath = array.at(array.size() - 1).toObject().value("details").toObject().value("beforeXPhotoPath").toString();

                        if (isBeforeAfterChanged) {
                            QPixmap afterPixmap = getQPixmapSync(afterXPhotoPath);

                            ui->pushButtonNImage->setIcon(QIcon(afterPixmap.scaled(ui->pushButtonNImage->width()
                                                                                   , ui->pushButtonNImage->height()
                                                                                   , Qt::IgnoreAspectRatio
                                                                                   , Qt::SmoothTransformation)));
                            ui->pushButtonNImage->setIconSize(QSize(252, 194));

                            QPixmap beforePixmap = getQPixmapSync(beforeXPhotoPath);

                            beforePixmap = beforePixmap.scaled(ui->labelXImage->width()
                                                               , ui->labelXImage->height()
                                                               , Qt::IgnoreAspectRatio
                                                               , Qt::SmoothTransformation);
                            ui->labelXImage->setPixmap(beforePixmap);
                        } else {
                            QPixmap afterPixmap = getQPixmapSync(afterXPhotoPath);

                            afterPixmap = afterPixmap.scaled(ui->labelXImage->width()
                                                             , ui->labelXImage->height()
                                                             , Qt::IgnoreAspectRatio
                                                             , Qt::SmoothTransformation);
                            ui->labelXImage->setPixmap(afterPixmap);

                            QPixmap beforePixmap = getQPixmapSync(beforeXPhotoPath);

                            ui->pushButtonNImage->setIcon(QIcon(beforePixmap.scaled(ui->pushButtonNImage->width()
                                                                                    , ui->pushButtonNImage->height()
                                                                                    , Qt::IgnoreAspectRatio
                                                                                    , Qt::SmoothTransformation)));
                            ui->pushButtonNImage->setIconSize(QSize(252, 194));
                        }
                    }

                    for (int i = 0; i < array.size(); i++) {

                    }
                }
            }
        }
    }
}

void MainWindow::onNewSerialData(QString strRequest)
{
    QNetworkRequest request;
    QNetworkAccessManager* naManager = new QNetworkAccessManager(this);

    connect(naManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(postResponse(QNetworkReply*)));

    // Header
    QString xLiveImageQuery = LocalSettings::instance()->value("Interface/queryUrl").toString();
    request.setUrl(QUrl(xLiveImageQuery));
    QString contentType = LocalSettings::instance()->value("Interface/contentType").toString();
    request.setHeader(QNetworkRequest::ContentTypeHeader, contentType);
    QString apiId = LocalSettings::instance()->value("Interface/apiId").toString();
    request.setRawHeader("apiId", apiId.toLatin1());
    QString timestamp = QDateTime::currentDateTime().toString("yyyyMMddhhmmss");
    request.setRawHeader("timestamp", timestamp.toLatin1());
    QString apiKey = LocalSettings::instance()->value("Interface/apiKey").toString();
    QString temp = xLiveImageQuery.mid(xLiveImageQuery.indexOf("/api/v1")) + timestamp + apiKey;
    QByteArray bb = QCryptographicHash::hash(temp.toLatin1(), QCryptographicHash::Md5);
    QString sign = QString().append(bb.toHex());
    request.setRawHeader("sign", sign.toLatin1());

    // Body
    QJsonObject json;
    QJsonDocument doc;
    QString uuid = QUuid::createUuid().toString();
    uuid.remove("{").remove("}").remove("-");
    json.insert("reqId", uuid);
    QString baseDeviceId = LocalSettings::instance()->value("Device/baseDeviceId").toString();
    json.insert("baseDeviceId", baseDeviceId);
    QString channelCode = LocalSettings::instance()->value("Device/channelCode").toString();
    json.insert("channelCode", channelCode);

    QJsonObject object;
    if (!parse(strRequest, object)) {
        return;
    }
    QString rfid = object.value("content").toObject().value("rfid").toString();
    json.insert("rfid", rfid);

    doc.setObject(json);
    QByteArray data = doc.toJson(QJsonDocument::Compact);

    naManager->post(request, data);
}

void MainWindow::on_pushButtonNImage_clicked()
{
    isBeforeAfterChanged = !isBeforeAfterChanged;

    if (isBeforeAfterChanged) {
        QPixmap afterPixmap = getQPixmapSync(afterXPhotoPath);

        ui->pushButtonNImage->setIcon(QIcon(afterPixmap.scaled(ui->pushButtonNImage->width()
                                                               , ui->pushButtonNImage->height()
                                                               , Qt::IgnoreAspectRatio
                                                               , Qt::SmoothTransformation)));
        ui->pushButtonNImage->setIconSize(QSize(252, 194));

        QPixmap beforePixmap = getQPixmapSync(beforeXPhotoPath);

        beforePixmap = beforePixmap.scaled(ui->labelXImage->width()
                                           , ui->labelXImage->height()
                                           , Qt::IgnoreAspectRatio
                                           , Qt::SmoothTransformation);
        ui->labelXImage->setPixmap(beforePixmap);
    } else {
        QPixmap afterPixmap = getQPixmapSync(afterXPhotoPath);

        afterPixmap = afterPixmap.scaled(ui->labelXImage->width()
                                         , ui->labelXImage->height()
                                         , Qt::IgnoreAspectRatio
                                         , Qt::SmoothTransformation);
        ui->labelXImage->setPixmap(afterPixmap);

        QPixmap beforePixmap = getQPixmapSync(beforeXPhotoPath);

        ui->pushButtonNImage->setIcon(QIcon(beforePixmap.scaled(ui->pushButtonNImage->width()
                                                                , ui->pushButtonNImage->height()
                                                                , Qt::IgnoreAspectRatio
                                                                , Qt::SmoothTransformation)));
        ui->pushButtonNImage->setIconSize(QSize(252, 194));
    }
}

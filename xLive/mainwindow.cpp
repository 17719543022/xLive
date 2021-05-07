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

    ui->tableWidgetRight->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableWidgetRight->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidgetRight->verticalHeader()->setVisible(false);
    ui->tableWidgetRight->horizontalHeader()->setVisible(false);
    ui->tableWidgetRight->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    ui->tableWidgetRight->setStyleSheet("border: none; background-color: rgb(1, 65, 109);");
    ui->tableWidgetRight->setShowGrid(false);
    ui->tableWidgetRight->setColumnCount(1);
    ui->tableWidgetRight->setColumnWidth(0, 766);

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

void MainWindow::doSetPixmap()
{
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

void MainWindow::fillTableTotally(QTableWidget *table, QJsonArray array)
{
    for (int i = 0; i < array.size(); i++) {
        QWidget *itemWidget = new QWidget();
        itemWidget->resize(table->width(), 230);

        QLabel *labelBackground = new QLabel(itemWidget);
        labelBackground->setGeometry(0, 0, table->width(), 230);
        labelBackground->setFixedSize(628, 230);
        labelBackground->setStyleSheet("image: 0; border: 0; background-color: rgb(1, 65, 109);");

        QLabel *labelRightBackground = new QLabel(itemWidget);
        labelRightBackground->setGeometry(0, 5, table->width(), 220);
        labelRightBackground->setFixedSize(628, 220);
        labelRightBackground->setStyleSheet("image: 0; border: 0; background-color: rgb(1, 31, 53);");

        QLabel *labelRightImage = new QLabel(itemWidget);
        labelRightImage->setGeometry(10, 15, 298, 200);
        labelRightImage->setFixedSize(298, 200);
        QPixmap afterPixmap = getQPixmapSync(array.at(i).toObject().value("details").toObject().value("afterXPhotoPath").toString());
        afterPixmap = afterPixmap.scaled(298
                                         , 200
                                         , Qt::IgnoreAspectRatio
                                         , Qt::SmoothTransformation);
        labelRightImage->setPixmap(afterPixmap);

        QLabel *labelRightText = new QLabel(itemWidget);
        labelRightText->setGeometry(318, 15, 300, 200);
        if (i == 0) {
            labelRightText->setText("第 一 次 检 查");
        } else if (i == 1) {
            labelRightText->setText("第 二 次 检 查");
        } else if (i == 2) {
            labelRightText->setText("第 三 次 检 查");
        } else if (i == 3) {
            labelRightText->setText("第 四 次 检 查");
        } else if (i == 4) {
            labelRightText->setText("第 五 次 检 查");
        } else if (i == 5) {
            labelRightText->setText("第 六 次 检 查");
        } else if (i == 6) {
            labelRightText->setText("第 七 次 检 查");
        } else if (i == 7) {
            labelRightText->setText("第 八 次 检 查");
        } else if (i == 8) {
            labelRightText->setText("第 九 次 检 查");
        } else if (i == 9) {
            labelRightText->setText("第 十 次 检 查");
        }
        labelRightText->setFixedSize(300, 200);
        labelRightText->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        labelRightText->setStyleSheet("image: 0; border: 0; background: transparent; font: 25pt; color: rgb(1, 195, 245);");

        ui->tableWidgetRight->insertRow(i);
        ui->tableWidgetRight->setRowHeight(i, 230);
        ui->tableWidgetRight->setCellWidget(i, 0, itemWidget);
    }

    connect(ui->tableWidgetRight, SIGNAL(cellClicked(int, int)), this, SLOT(on_cellClicked(int, int)));
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

                        afterXPhotoPath = array.at(0).toObject().value("details").toObject().value("afterXPhotoPath").toString();
                        beforeXPhotoPath = array.at(0).toObject().value("details").toObject().value("beforeXPhotoPath").toString();

                        this->doSetPixmap();
                    }

                    this->fillTableTotally(ui->tableWidgetRight, array);
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

    this->doSetPixmap();
}

void MainWindow::on_cellClicked(int row, int column)
{
    Q_UNUSED(column)

    QJsonObject obj = document.object();

    if (obj.contains("results")) {
        QJsonValue results = obj.value("results");
        if (results.isArray()) {
            array = results.toArray();

            if (array.size() > row) {
                afterXPhotoPath = array.at(row).toObject().value("details").toObject().value("afterXPhotoPath").toString();
                beforeXPhotoPath = array.at(row).toObject().value("details").toObject().value("beforeXPhotoPath").toString();

                this->doSetPixmap();
            }
        }
    }
}

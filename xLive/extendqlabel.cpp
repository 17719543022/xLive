#include "extendqlabel.h"
#include <QDebug>
#include <QPainter>
#include <QAction>
#include "settings.h"
#include <QJsonObject>
#include <QJsonDocument>
#include <QUuid>
#include <QDir>
#include <QBuffer>

Frame::Frame()
    : currentPath(QString())
    , currentId(QString())
    , begin(QPoint())
    , end(QPoint())
    , value(QString())
    , valueId(0)
    , isValid(false)
{

}

void Frame::dump()
{
    if (isValid) {
        qDebug() << "currentPath: " << currentPath;
        qDebug() << "currentId: " << currentId;
        qDebug() << "begin: " << begin;
        qDebug() << "end: " << end;
        qDebug() << "value: " << value;
        qDebug() << "valueId: " << valueId;
    }
}

extendQLabel::extendQLabel(QWidget *parent)
    : QLabel(parent)
    , isMousePressed(false)
    , currentPath(QString())
    , currentId(QString())
    , currentPixmap(QPixmap())
    , currentWidth(0)
    , currentHeight(0)
    , rfid(QString())
    , value(QString())
    , valueId(0)
{
    this->on_Load();
}

void extendQLabel::on_LoadResponse(QNetworkReply* reply)
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
            qDebug() << "document: " << document;

            dictoryArray = obj.value("results").toObject().value("9").toArray();

            m_menu1 = new QMenu();
            QFile file("../xLive/menu.css");
            if (file.open(QFile::ReadOnly)) {
                QString qss = QLatin1String(file.readAll());
                m_menu1->setStyleSheet(qss);
                file.close();
            }
            for (int i = 0; i < dictoryArray.size(); i++) {
                m_menu1->addAction(dictoryArray.at(i).toObject().value("value").toString(), this, SLOT(actionsSlot()));
                m_menu1->addSeparator();
            }
        }
    }
}

void extendQLabel::on_Load()
{
    QNetworkRequest request;
    QNetworkAccessManager *naManager = new QNetworkAccessManager(this);

    connect(naManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(on_LoadResponse(QNetworkReply*)));

    // Header
    QString dictoryQuery = LocalSettings::instance()->value("Interface/dictoryUrl").toString();
    request.setUrl(QUrl(dictoryQuery));
    QString contentType = LocalSettings::instance()->value("Interface/contentType").toString();
    request.setHeader(QNetworkRequest::ContentTypeHeader, contentType);
    QString apiId = LocalSettings::instance()->value("Interface/apiId").toString();
    request.setRawHeader("apiId", apiId.toLatin1());
    QString timestamp = QDateTime::currentDateTime().toString("yyyyMMddhhmmss");
    request.setRawHeader("timestamp", timestamp.toLatin1());
    QString apiKey = LocalSettings::instance()->value("Interface/apiKey").toString();
    QString temp = dictoryQuery.mid(dictoryQuery.indexOf("/api/v1")) + timestamp + apiKey;
    QByteArray bb = QCryptographicHash::hash(temp.toLatin1(), QCryptographicHash::Md5);
    QString sign = QString().append(bb.toHex());
    request.setRawHeader("sign", sign.toLatin1());

    // Body
    QJsonObject json;
    QJsonDocument doc;
    QString uuid = QUuid::createUuid().toString();
    uuid.remove("{").remove("}").remove("-");
    json.insert("reqId", uuid);
    json.insert("typeId", 9);

    doc.setObject(json);
    QByteArray data = doc.toJson(QJsonDocument::Compact);

    naManager->post(request, data);
}

void extendQLabel::on_hazardousResponse(QNetworkReply *reply)
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

        if (document.object().value("status").toInt() == 0) {
            this->setFrames();
            update();

            emit this->uploadSuccess(document.object().value("newPhotoPath").toString());
        }
    }
}

void extendQLabel::upLoad()
{
    bool canIUpLoadFrames = false;

    QNetworkRequest request;
    QNetworkAccessManager *naManager = new QNetworkAccessManager(this);

    connect(naManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(on_hazardousResponse(QNetworkReply*)));

    // Header
    QString hazardousUrl = LocalSettings::instance()->value("Interface/hazardousUrl").toString();
    request.setUrl(QUrl(hazardousUrl));
    QString contentType = LocalSettings::instance()->value("Interface/contentType").toString();
    request.setHeader(QNetworkRequest::ContentTypeHeader, contentType);
    QString apiId = LocalSettings::instance()->value("Interface/apiId").toString();
    request.setRawHeader("apiId", apiId.toLatin1());
    QString timestamp = QDateTime::currentDateTime().toString("yyyyMMddhhmmss");
    request.setRawHeader("timestamp", timestamp.toLatin1());
    QString apiKey = LocalSettings::instance()->value("Interface/apiKey").toString();
    QString temp = hazardousUrl.mid(hazardousUrl.indexOf("/api/v1")) + timestamp + apiKey;
    QByteArray bb = QCryptographicHash::hash(temp.toLatin1(), QCryptographicHash::Md5);
    QString sign = QString().append(bb.toHex());
    request.setRawHeader("sign", sign.toLatin1());

    // Body
    QJsonObject json;
    QJsonDocument doc;
    QString uuid = QUuid::createUuid().toString();
    uuid.remove("{").remove("}").remove("-");
    json.insert("reqId", uuid);
    json.insert("rfid", rfid);
    QString baseDeviceId = LocalSettings::instance()->value("Device/baseDeviceId").toString();
    json.insert("baseDeviceId", baseDeviceId);
    QString channelCode = LocalSettings::instance()->value("Device/channelCode").toString();
    json.insert("channelCode", channelCode);
    json.insert("processNode", 8);
    QJsonObject extraInfo;
    extraInfo.insert("imageExtraInfoId", currentId);
    QJsonArray imageExtraInfo;
    for (int i = 0; i < 10; i++) {
        if (frames[i].isValid) {
            canIUpLoadFrames = true;

            QJsonObject item;
            item.insert("beginx", int(frames[i].begin.x() * currentWidth / this->width()));
            item.insert("beginy", int(frames[i].begin.y() * currentHeight / this->height()));
            item.insert("endx", int(frames[i].end.x() * currentWidth / this->width()));
            item.insert("endy", int(frames[i].end.y() * currentHeight / this->height()));
            item.insert("value", frames[i].value);
            item.insert("valueId", frames[i].valueId);
            imageExtraInfo.push_back(item);
        }
    }
    extraInfo.insert("imageExtraInfo", imageExtraInfo);
    json.insert("extraInfo", extraInfo);

    QPainter painter(&currentPixmap);
    painter.begin(&currentPixmap);
    painter.setPen(QPen(Qt::red, 2));
    QFont font;
    font.setPointSize(20);
    painter.setFont(font);
    for (int i = 0; i < 10; i++) {
        if (frames[i].isValid) {
            painter.drawRect(QRect(QPoint(int(frames[i].begin.x() * currentWidth / this->width()), int(frames[i].begin.y() * currentHeight / this->height())), QPoint(int(frames[i].end.x() * currentWidth / this->width()), int(frames[i].end.y() * currentHeight / this->height()))));
            painter.drawText(QPoint(qMax(int(frames[i].begin.x() * currentWidth / this->width()), int(frames[i].end.x() * currentWidth / this->width())), qMin(int(frames[i].begin.y() * currentHeight / this->height()), int(frames[i].end.y() * currentHeight / this->height()))), frames[i].value);
        }
    }
    QByteArray byteArray;
    QBuffer buffer(&byteArray);
    buffer.open(QIODevice::WriteOnly);
    currentPixmap.save(&buffer, "JPG");
    buffer.close();
    QJsonArray imgs;
    QJsonObject jsonObject;
    jsonObject.insert("imgData", QString::fromLocal8Bit(byteArray.toBase64()));
    jsonObject.insert("photoName", QString());
    imgs.push_back(jsonObject);
    json.insert("imgs", imgs);

    qDebug() << "json: " << json;

    doc.setObject(json);
    QByteArray data = doc.toJson(QJsonDocument::Compact);

    if (canIUpLoadFrames) {
        naManager->post(request, data);
    } else {
        emit this->uploadFailed();
    }
}

void extendQLabel::setCurrentPath(QString str)
{
    currentPath = str;
}

void extendQLabel::setCurrentId(QString str)
{
    currentId = str;
}

void extendQLabel::setCurrentPixmap(QPixmap pixmap)
{
    currentPixmap = pixmap;
}

void extendQLabel::setCurrentWidth(int width)
{
    currentWidth = width;
}

void extendQLabel::setCurrentHeight(int height)
{
    currentHeight = height;
}

void extendQLabel::setRfid(QString str)
{
    rfid = str;
}

void extendQLabel::setFrames()
{
    for (int i = 0; i < 10; i++) {
        frames[i].currentPath = QString();
        frames[i].currentId = QString();
        frames[i].begin = QPoint();
        frames[i].end = QPoint();
        frames[i].value = QString();
        frames[i].valueId = 0;
        frames[i].isValid = false;
    }

    currentWidth = 0;
    currentHeight = 0;
}

bool extendQLabel::isFramesExists()
{
    bool isFramesExist = false;

    for (int i = 0; i < 10; i++) {
        if (frames[i].isValid) {
            isFramesExist = true;
            break;
        }
    }

    return isFramesExist;
}

void extendQLabel::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        isMousePressed = true;

        begin = event->pos();
    }
}

void extendQLabel::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        end = event->pos();
        isMousePressed = false;
        update();

        if ((qAbs(end.x() - begin.x()) > 15) && (qAbs(end.y() - begin.y()) > 15)) {
            m_menu1->exec(cursor().pos());
        }
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
    QFont font;
    font.setPointSize(17);
    painter.setFont(font);

    if (isMousePressed)
    {
        painter.drawRect(QRect(begin, mid));
    } else {
        if (value != QString()) {
            for (int i = 0; i < 10; i++) {
                if (!frames[i].isValid) {
                    frames[i].currentPath = currentPath;
                    frames[i].currentId = currentId;
                    frames[i].begin = begin;
                    frames[i].end = end;
                    frames[i].value = value;
                    frames[i].valueId = valueId;
                    frames[i].isValid = true;
                    break;
                }
            }

            begin = QPoint();
            end = QPoint();
            value = QString();
        }

        if ((qAbs(end.x() - begin.x()) > 15) && (qAbs(end.y() - begin.y()) > 15)) {
            painter.drawRect(QRect(begin, end));
        } else {
            painter.eraseRect(QRect(begin, end));
        }
    }

    for (int k = 0; k < 10; k++) {
        if (frames[k].isValid) {
            painter.drawRect(QRect(frames[k].begin, frames[k].end));
            painter.drawText(QPoint(qMax(frames[k].begin.x(), frames[k].end.x()), qMin(frames[k].begin.y(), frames[k].end.y())), frames[k].value);
        }
    }
}

void extendQLabel::actionsSlot()
{
    QAction *action = (QAction *)sender();
    value = action->text();
    for (int i = 0; i < dictoryArray.size(); i++) {
        if (dictoryArray.at(i).toObject().value("value").toString() == value) {
            valueId = dictoryArray.at(i).toObject().value("valueId").toInt();
            break;
        }
    }

    update();
}

void extendQLabel::contextMenuEvent(QContextMenuEvent *ev)
{
//    m_menu1->exec(cursor().pos());
    ev->accept();
}

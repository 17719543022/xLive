#include "extendqlabel.h"
#include <QDebug>
#include <QPainter>
#include <QAction>
#include "settings.h"
#include <QJsonObject>
#include <QJsonDocument>
#include <QUuid>

Frame::Frame()
    : currentPath(QString())
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
    , value(QString())
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
            for (int i = 0; i < dictoryArray.size(); i++) {
                if (dictoryArray.at(i).toObject().value("level").toInt() == 1) {
                    QMenu *m_menu2 = m_menu1->addMenu(dictoryArray.at(i).toObject().value("value").toString());
                    for (int j = 0; j < dictoryArray.size(); j++) {
                        if ((dictoryArray.at(j).toObject().value("level").toInt() == 2)
                                && (dictoryArray.at(j).toObject().value("parentId").toInt() == dictoryArray.at(i).toObject().value("valueId").toInt())) {
                            int isValidParent = false;
                            for (int l = 0; l < dictoryArray.size(); l++) {
                                if ((dictoryArray.at(l).toObject().value("level").toInt() == 3)
                                        && (dictoryArray.at(l).toObject().value("parentId").toInt() == dictoryArray.at(j).toObject().value("valueId").toInt())) {
                                    isValidParent = true;
                                }
                            }
                            if (isValidParent) {
                                QMenu *m_menu3 = m_menu2->addMenu(dictoryArray.at(j).toObject().value("value").toString());
                                for (int k = 0; k < dictoryArray.size(); k++) {
                                    if ((dictoryArray.at(k).toObject().value("level").toInt() == 3)
                                            && (dictoryArray.at(k).toObject().value("parentId").toInt() == dictoryArray.at(j).toObject().value("valueId").toInt())) {
                                        m_menu3->addAction(dictoryArray.at(k).toObject().value("value").toString(), this, SLOT(actionsSlot()));
                                    }
                                }
                            } else {
                                m_menu2->addAction(dictoryArray.at(j).toObject().value("value").toString(), this, SLOT(actionsSlot()));
                            }
                        }
                    }
                }
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

}

void extendQLabel::upLoad()
{
//    qDebug() << "currentPath: " << currentPath;
//    for (int i = 0; i < 10; i++) {
//        qDebug() << "i: " << i;
//        frames[i].dump();
//    }

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
    QString baseDeviceId = LocalSettings::instance()->value("Device/baseDeviceId").toString();
    json.insert("baseDeviceId", baseDeviceId);
    QString channelCode = LocalSettings::instance()->value("Device/channelCode").toString();
    json.insert("channelCode", channelCode);
    json.insert("processNode", 8);
    QJsonObject extraInfo;
    extraInfo.insert("imageExtraInfoId", currentPath);
    QJsonArray imageExtraInfo;
    for (int i = 0; i < 10; i++) {
        if (frames[i].isValid) {
            QJsonObject item;
            item.insert("beginx", frames[i].begin.x());
            item.insert("beginy", frames[i].begin.y());
            item.insert("endx", frames[i].end.x());
            item.insert("endy", frames[i].end.y());
            item.insert("value", frames[i].value);
            item.insert("valueId", frames[i].valueId);
            imageExtraInfo.push_back(item);
        }
    }
    extraInfo.insert("imageExtraInfo", imageExtraInfo);
    json.insert("extraInfo", extraInfo);

    qDebug() << "json: " << json;

    doc.setObject(json);
    QByteArray data = doc.toJson(QJsonDocument::Compact);

    naManager->post(request, data);
}

void extendQLabel::setCurrentPath(QString str)
{
    currentPath = str;
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

    if (isMousePressed)
    {
        painter.drawRect(QRect(begin, mid));
    } else {
        if (value != QString()) {
            for (int i = 0; i < 10; i++) {
                if (!frames[i].isValid) {
                    frames[i].currentPath = currentPath;
                    frames[i].begin = begin;
                    frames[i].end = end;
                    frames[i].value = value;
                    frames[i].valueId = 0;
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

    update();
}

void extendQLabel::contextMenuEvent(QContextMenuEvent *ev)
{
//    m_menu1->exec(cursor().pos());
    ev->accept();
}

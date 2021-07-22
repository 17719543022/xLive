#include "extendqlabel.h"
#include <QDebug>
#include <QPainter>
#include <QAction>
#include "settings.h"
#include <QJsonObject>
#include <QJsonDocument>
#include <QUuid>

extendQLabel::extendQLabel(QWidget *parent)
    : QLabel(parent)
    , isMousePress(false)
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
                            QMenu *m_menu3 = m_menu2->addMenu(dictoryArray.at(j).toObject().value("value").toString());
                            for (int k = 0; k < dictoryArray.size(); k++) {
                                if ((dictoryArray.at(k).toObject().value("level").toInt() == 3)
                                        && (dictoryArray.at(k).toObject().value("parentId").toInt() == dictoryArray.at(j).toObject().value("valueId").toInt())) {
                                    m_menu3->addAction(dictoryArray.at(k).toObject().value("value").toString(), this, SLOT(actionsSlot()));
                                }
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
    QNetworkAccessManager* naManager = new QNetworkAccessManager(this);

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

void extendQLabel::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        isMousePress = true;

        begin = event->pos();
    }
}

void extendQLabel::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        end = event->pos();
        isMousePress = false;
        update();
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

    if (isMousePress)
    {
      painter.drawRect(QRect(begin, mid));
    } else {
      painter.drawRect(QRect(begin, end));
    }
}

void extendQLabel::actionsSlot()
{
    QAction *action = (QAction *)sender();
    QString actionText = action->text();

    qDebug() << actionText << "triggered!";

    if ("1_1" == actionText) {
        qDebug() << "1_1";
    } else if ("1_2" == actionText) {
        qDebug() << "1_2";
    } else if ("1_3" == actionText) {
        qDebug() << "1_3";
    } else if ("1_4" == actionText) {
        qDebug() << "1_4";
    } else {
        qDebug() << actionText;
    }
}

void extendQLabel::contextMenuEvent(QContextMenuEvent *ev)
{
    m_menu1->exec(cursor().pos());
    ev->accept();
}

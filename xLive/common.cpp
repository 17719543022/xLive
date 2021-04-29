#include "common.h"
#include <QJsonParseError>
#include "QDebug"

bool parse(const QString &str, QJsonObject &object)
{
    QJsonParseError jsonParseError;
    QJsonDocument document = QJsonDocument::fromJson(str.toUtf8(), &jsonParseError);

    if (!document.isNull() && jsonParseError.error == QJsonParseError::NoError) {
        object = document.object();

        return true;
    }

    qDebug() << "QJsonParseError: " << jsonParseError.error;
    return false;
}

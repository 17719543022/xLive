#include "listener.h"
#include "QDebug"
#include "QJsonObject"
#include "common.h"

Listener::Listener()
{

}

void Listener::MultipartRequstListen(const std::string &uri, const std::map<std::string, DataInfo> &mapDataInfo, std::string &strResponse)
{
    Q_UNUSED(mapDataInfo)
    qDebug() << "uri: " << QString::fromLocal8Bit(uri.c_str());

    strResponse = "{\"reqId\":\"123\",\"status\":0,\"msg\":\"success\",\"faceNum\":1,\"faceInfo\":[{\"userInfo\":\"\",\"imgUrl\":\"\",\"score\":0.78349584,\"result\":1,\"uId\":\"\",\"fId\":\"1\"}]}";
}

void Listener::CommonRequstListen(const std::string &uri, const std::string &strRequestBody, std::string &strResponse)
{
    Q_UNUSED(uri)
    Q_UNUSED(strResponse)

    emit this->stateNetworkChange(true);

    QJsonObject object;
    if (!parse(QString::fromLocal8Bit(strRequestBody.c_str()), object)) {
        return;
    }

    // 10-开包位读取
    if (object.value("content").toObject().value("type").toInt() == 10) {
        emit this->newSerialData(QString::fromLocal8Bit(strRequestBody.c_str()));
    }
}

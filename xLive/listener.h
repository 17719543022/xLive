#ifndef LISTENER_H
#define LISTENER_H

#include <QObject>
#include "HTTPServer/HTTPServerExp.h"

class Listener : public QObject, public RequstListener
{
    Q_OBJECT

public:
    Listener();

private:
    virtual void MultipartRequstListen(const std::string& uri, const std::map<std::string, DataInfo>& mapDataInfo, std::string& strResponse);
    virtual void CommonRequstListen(const std::string& uri, const std::string& strRequestBody, std::string& strResponse);

signals:
    void newLeaveBeltXLive(QString strRequest);
    void newOpenLuggageXLive(QString strRequest);
    void stateNetworkChange(bool state);
};


#endif // LISTENER_H

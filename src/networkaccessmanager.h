#ifndef NETWORKACCESSMANAGER_H
#define NETWORKACCESSMANAGER_H


#include <QObject>
#include <QScopedPointer>
#include <inetworkaccessmanager.h>

namespace networking {

class NetworkAccessManager: public QObject, public INetworkAccessManager
{
    Q_OBJECT

public:
    explicit NetworkAccessManager(QObject* parent = nullptr);
    ~NetworkAccessManager() override;
    QNetworkReply* get(const QNetworkRequest& request) override;
    bool isNetworkAccessible() const override;

private:
    class NetworkAccessManagerImp;
    QScopedPointer<NetworkAccessManagerImp> networkAccessImpl;
};
}

#endif // NETWORKACCESSMANAGER_H

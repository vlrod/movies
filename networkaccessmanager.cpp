#include "networkaccessmanager.h"

#include <QNetworkAccessManager>

namespace networking {

class NetworkAccessManager::NetworkAccessManagerImp
{
public:
    NetworkAccessManagerImp() {}

    QNetworkAccessManager networkAccessManager;
};

NetworkAccessManager::NetworkAccessManager(QObject *parent)
    : QObject(parent)
{
    networkAccessImpl.reset(new NetworkAccessManagerImp());
}

NetworkAccessManager::~NetworkAccessManager()
{
}

QNetworkReply* NetworkAccessManager::get(const QNetworkRequest& request)
{
    return networkAccessImpl->networkAccessManager.get(request);
}

bool NetworkAccessManager::isNetworkAccessible() const
{
    return networkAccessImpl->networkAccessManager.networkAccessible() == QNetworkAccessManager::Accessible;
}
}

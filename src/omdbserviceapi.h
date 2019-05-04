#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "networkaccessmanager.h"
#include "webrequest.h"
#include <QObject>
#include <memory>

using namespace networking;

class OmdbServiceApi: public QObject
{
    Q_OBJECT
public:
    OmdbServiceApi();
    explicit OmdbServiceApi(std::shared_ptr<IWebRequest> wRequest);
    void searchMovieByName(const QString& name);
    void searchMovieByNameAndType(const QString& name, const QString& type);

private:
    QUrl buildUrl(const QUrlQuery& query);

private:
    std::shared_ptr<NetworkAccessManager> networkAccessManager;
    std::shared_ptr<IWebRequest> webResquest;
signals:
    void searchComplete(int statusCode, const QByteArray& body);

};

#endif // CONTROLLER_H

#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "networkaccessmanager.h"
#include "webrequest.h"
#include <QObject>

using namespace networking;

class OmdbServiceApi: public QObject
{
    Q_OBJECT
public:
    OmdbServiceApi();
    void searchMovieByName(const QString& name);
    void searchMovieByNameAndType(const QString& name, const QString& type);

private:
    void makeRequest(const QString& name, const QString& type = nullptr);

private:
    NetworkAccessManager* networkAccessManager{nullptr};
    WebRequest* webRequest{nullptr};

public slots:
    void onReplyReceived(int statusCode, const QByteArray& body);

};

#endif // CONTROLLER_H

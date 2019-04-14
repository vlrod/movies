#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "networkaccessmanager.h"
#include "webrequest.h"
#include <QObject>

using namespace networking;

class Controller: public QObject
{
    Q_OBJECT
public:
    Controller();
    void searchMovieByName(const QString& name);

private:
    NetworkAccessManager* networkAccessManager{nullptr};
    WebRequest* webRequest{nullptr};

public slots:
    void onReplyReceived(int statusCode, const QByteArray& body);

};

#endif // CONTROLLER_H

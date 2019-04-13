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
    void searchMovieByName(QString name);

private:
    NetworkAccessManager* networkAccessManager{nullptr};
    WebRequest* rssWebRequest{nullptr};

public slots:
    void onRssReplyReceived(int statusCode, QByteArray body);

};

#endif // CONTROLLER_H

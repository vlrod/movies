#include "controller.h"
#include <qjsondocument.h>
#include <QVariant>
#include <QUrlQuery>

Controller::Controller()
{
    networkAccessManager = new NetworkAccessManager(this);
    rssWebRequest = new WebRequest(this, networkAccessManager);
    QObject::connect(rssWebRequest, &WebRequest::requestComplete, this, &Controller::onRssReplyReceived);
}

void Controller::searchMovieByName(QString name)
{
    QVariantMap feed;
    feed.insert("api_key","9888f455");
    QUrlQuery query;
    query.addQueryItem("apikey","9888f455");
    query.addQueryItem("t", name);

    QUrl url;
    url.setScheme("http");
    url.setHost("www.omdbapi.com");
    url.setQuery(query);
    rssWebRequest->get(url);
}

void Controller::onRssReplyReceived(int statusCode, QByteArray body)
{
    qDebug() << "Received response code " << statusCode << ":";
    qDebug() << body;
}

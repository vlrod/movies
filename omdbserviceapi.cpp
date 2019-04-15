#include "omdbserviceapi.h"
#include <qjsondocument.h>
#include <QVariant>
#include <QUrlQuery>

OmdbServiceApi::OmdbServiceApi()
{
    networkAccessManager = new NetworkAccessManager(this);
    webRequest = new WebRequest(this, networkAccessManager);
    QObject::connect(webRequest, &WebRequest::requestComplete, this, &OmdbServiceApi::onReplyReceived);
}

void OmdbServiceApi::searchMovieByName(const QString& name)
{
    QUrlQuery query;
    query.addQueryItem("apikey","9888f455");
    query.addQueryItem("t", name);

    QUrl url;
    url.setScheme("http");
    url.setHost("www.omdbapi.com");
    url.setQuery(query);
    webRequest->get(url);
}

void OmdbServiceApi::onReplyReceived(int statusCode, const QByteArray& body)
{
    qDebug() << "Received response code " << statusCode << ":";
    qDebug() << body;
}
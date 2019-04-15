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
    this->makeRequest(name);
}

void OmdbServiceApi::searchMovieByNameAndType(const QString& name, const QString& type)
{
    this->makeRequest(name, type);
}

void OmdbServiceApi::makeRequest(const QString& name, const QString& type)
{
    QUrl url;
    url.setScheme("http");
    url.setHost("www.omdbapi.com");
    QUrlQuery query;
    query.addQueryItem("apikey","9888f455");
    query.addQueryItem("t", name);
    if (type != nullptr) {
        query.addQueryItem("type", type);
    }

    url.setQuery(query);
    webRequest->get(url);
}

void OmdbServiceApi::onReplyReceived(int statusCode, const QByteArray& body)
{
    qDebug() << "Received response code " << statusCode << ":";
    qDebug() << body;
}

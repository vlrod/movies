#include "omdbserviceapi.h"
#include <qjsondocument.h>
#include <QVariant>
#include <QUrlQuery>

OmdbServiceApi::OmdbServiceApi()
{
    networkAccessManager = new NetworkAccessManager(this);
    webRequest = new WebRequest(this, networkAccessManager);
    QObject::connect(webRequest, &WebRequest::requestComplete, this, &OmdbServiceApi::searchComplete);
}

void OmdbServiceApi::searchMovieByName(const QString& name)
{
    QUrlQuery query;
    query.addQueryItem("t", name);
    webRequest->get(buildUrl(query));
}

void OmdbServiceApi::searchMovieByNameAndType(const QString& name, const QString& type)
{
    QUrlQuery query;
    query.addQueryItem("t", name);
    query.addQueryItem("type", type);
    webRequest->get(buildUrl(query));
}

QUrl OmdbServiceApi::buildUrl(const QUrlQuery& query)
{
    QUrl url;
    url.setScheme("http");
    url.setHost("www.omdbapi.com");
    QUrlQuery baseQuery(query);
    baseQuery.addQueryItem("apikey","9888f455");
    url.setQuery(baseQuery);
    return url;
}

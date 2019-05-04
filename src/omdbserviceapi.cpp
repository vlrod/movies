#include "omdbserviceapi.h"
#include <qjsondocument.h>
#include <QVariant>
#include <QUrlQuery>

OmdbServiceApi::OmdbServiceApi()
{
    networkAccessManager = std::make_shared<NetworkAccessManager>();
    webResquest = std::make_shared<WebRequest>(this, networkAccessManager.get());
    QObject::connect(std::static_pointer_cast<WebRequest>(webResquest).get(), &WebRequest::requestComplete, this, &OmdbServiceApi::searchComplete);
}

OmdbServiceApi::OmdbServiceApi(std::shared_ptr<IWebRequest> wRequest): webResquest(wRequest)
{
   QObject::connect(dynamic_cast<QObject*>(webResquest.get()), SIGNAL(requestComplete(int, QByteArray)), this, SIGNAL(searchComplete(int, QByteArray)));
}

void OmdbServiceApi::searchMovieByName(const QString& name)
{
    QUrlQuery query;
    query.addQueryItem("t", name);
    webResquest->get(buildUrl(query));
}

void OmdbServiceApi::searchMovieByNameAndType(const QString& name, const QString& type)
{
    QUrlQuery query;
    query.addQueryItem("t", name);
    query.addQueryItem("type", type);
    webResquest->get(buildUrl(query));
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

#include "webrequest.h"
#include <QMap>
#include <QNetworkReply>
#include <QNetworkRequest>

namespace networking {

static const QMap<QNetworkReply::NetworkError, QString> networkErrorMapper = {
    { QNetworkReply::ConnectionRefusedError, "The remote server refused the connection (the server is not accepting requests)."},
    { QNetworkReply::RemoteHostClosedError, "The remote server closed the connection prematurely, before the entire reply was received and processed"},
    { QNetworkReply::HostNotFoundError, "The remote host name was not found (invalid hostname)"},
    { QNetworkReply::TimeoutError, "The connection to the remote server timed out"},
    { QNetworkReply::OperationCanceledError, "The operation was canceled via calls to abort() or close() before it was finished."},
    { QNetworkReply::OperationCanceledError, "The operation was canceled via calls to abort() or close() before it was finished."},
    { QNetworkReply::SslHandshakeFailedError, "The SSL/TLS handshake failed and the encrypted channel could not be established. The sslErrors() signal should have been emitted."},
    { QNetworkReply::InternalServerError, "The server encountered an unexpected condition which prevented it from fulfilling the request."},
    { QNetworkReply::UnknownServerError, "An unknown error related to the server response was detected."}
};

class WebRequest::WebRequestImpl
{

public:
    WebRequestImpl(WebRequest* _webRequest, INetworkAccessManager* _networkAccessManager)
        : webRequest(_webRequest)
        , networkAccessManager(_networkAccessManager)
    {}
    WebRequest* webRequest{nullptr};
    INetworkAccessManager* networkAccessManager{ nullptr };
    QUrl url {};
    QNetworkReply* reply{nullptr};

public:
    bool isBusy() const
    {
        return m_isBusy;
    }
    void setIsBusy(bool value)
    {
        if (value != m_isBusy) {
            m_isBusy = value;
            emit webRequest->isBusyChanged();
        }
    }
private:
    bool m_isBusy{false};
};


WebRequest::WebRequest(QObject* parent, INetworkAccessManager* networkAccessManager)
    : QObject(parent)
    , IWebRequest()
{
    webRequestImpl.reset(new WebRequest::WebRequestImpl(this, networkAccessManager));
}

WebRequest::~WebRequest()
{
}

void WebRequest::get(QUrl url)
{
    if (webRequestImpl->isBusy()) {
        return;
    }

    if(!webRequestImpl->networkAccessManager->isNetworkAccessible()) {
        emit error("Network not accessible");
        return;
    }

    webRequestImpl->setIsBusy(true);
    QNetworkRequest request;
    request.setUrl(url);
    webRequestImpl->reply = webRequestImpl->networkAccessManager->get(request);
    if(webRequestImpl->reply != nullptr) {
        connect(webRequestImpl->reply, &QNetworkReply::finished, this, &WebRequest::replyDelegate);
        connect(webRequestImpl->reply, &QNetworkReply::sslErrors, this, &WebRequest::sslErrorsDelegate);
    }
}

bool WebRequest::isBusy() const
{
    return webRequestImpl->isBusy();
}

void WebRequest::setUrl(const QUrl& url)
{
    if(url != webRequestImpl->url) {
        webRequestImpl->url = url;
        emit urlChanged();
    }
}

QUrl WebRequest::url() const
{
    return webRequestImpl->url;
}

void WebRequest::replyDelegate()
{
    webRequestImpl->setIsBusy(false);
    if (webRequestImpl->reply == nullptr) {
        emit error("Unexpected error - reply object is null");
        return;
    }
    disconnect(webRequestImpl->reply, &QNetworkReply::finished, this, &WebRequest::replyDelegate);
    disconnect(webRequestImpl->reply, &QNetworkReply::sslErrors, this, &WebRequest::sslErrorsDelegate);
    auto statusCode = webRequestImpl->reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
    auto responseBody = webRequestImpl->reply->readAll();
    auto replyStatus = webRequestImpl->reply->error();
    webRequestImpl->reply->deleteLater();
    if (replyStatus != QNetworkReply::NoError) {
        emit error(networkErrorMapper[webRequestImpl->reply->error()]);
    }
    emit requestComplete(statusCode, responseBody);
}

void WebRequest::sslErrorsDelegate(const QList<QSslError>& errors)
{
    QString sslError;
    for (const auto& error : errors) {
        sslError += error.errorString() + "\n";
    }
    emit error(sslError);
}
}

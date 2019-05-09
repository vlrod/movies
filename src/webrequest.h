#ifndef WEBREQUEST_H
#define WEBREQUEST_H

#include "inetworkaccessmanager.h"
#include "iwebrequest.h"
#include <QList>
#include <QObject>
#include <QSslError>

namespace networking {
class WebRequest : public QObject, public IWebRequest
{
    Q_OBJECT

public:
    WebRequest(QObject* parent, INetworkAccessManager* networkAccessManager);
    WebRequest(QObject* parent = nullptr) = delete;
    ~WebRequest() override;
    void get(QUrl url) override;
    bool isBusy() const override;
    void setUrl(const QUrl& url) override;
    QUrl url() const override;

signals:
    void error(QString message);
    void isBusyChanged();
    void requestComplete(int statusCode, QByteArray body) override;
    void urlChanged();

private slots:
    void replyDelegate();
    void sslErrorsDelegate( const QList<QSslError>& _errors );

private:
    class WebRequestImpl;
    QScopedPointer<WebRequestImpl> webRequestImpl;
};
}

#endif // WEBREQUEST_H

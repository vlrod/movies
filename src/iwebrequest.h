#ifndef IWEBREQUEST_H
#define IWEBREQUEST_H
#include <QUrl>

namespace networking {
class IWebRequest
{
public:
    IWebRequest(){}
    virtual ~IWebRequest(){}
    virtual void get(QUrl url) = 0;
    virtual bool isBusy() const = 0;
    virtual void setUrl(const QUrl& url) = 0;
    virtual QUrl url() const = 0;

signals:
    virtual void requestComplete(int statusCode, QByteArray body) = 0;
};
}

#endif // IWEBREQUEST_H

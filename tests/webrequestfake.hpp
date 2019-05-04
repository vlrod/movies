#ifndef WEBREQUESTFAKE_H
#define WEBREQUESTFAKE_H

#include <QCoreApplication>
#include "omdbserviceapi.h"
#include "iwebrequest.h"
#include "inetworkaccessmanager.h"
#include <iostream>
#include <memory>

class WebRequestFake: public QObject, public IWebRequest
{
    Q_OBJECT

public:
    WebRequestFake() {}
    ~WebRequestFake() {}
    void get(QUrl url) {
        Q_UNUSED(url);
    }
    bool isBusy() const { return false;}
    void setUrl(const QUrl& url) { Q_UNUSED(url);}
    QUrl url() const {
        const QUrl url;
        return url;
    }

signals:
    void requestComplete(int statusCode, QByteArray body);
};


#endif // WEBREQUESTFAKE_H

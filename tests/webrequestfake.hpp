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
        // FIXME: read from file
        QByteArray data("{\"Title\":\"Game of Thrones\",\"Year\":\"2011–\",\"Rated\":\"TV-MA\",\"Released\":\"17 Apr 2011\",\"Runtime\":\"57 min\",\"Genre\":\"Action, Adventure, Drama, Fantasy, Romance\",\"Director\":\"N/A\",\"Writer\":\"David Benioff, D.B. Weiss\",\"Actors\":\"Peter Dinklage, Lena Headey, Emilia Clarke, Kit Harington\",\"Plot\":\"Nine noble families fight for control over the mythical lands of Westeros, while an ancient enemy returns after being dormant for thousands of years.\",\"Language\":\"English\",\"Country\":\"USA, UK\",\"Awards\":\"Won 1 Golden Globe. Another 273 wins & 454 nominations.\",\"Poster\":\"https://m.media-amazon.com/images/M/MV5BMjA5NzA5NjMwNl5BMl5BanBnXkFtZTgwNjg2OTk2NzM@._V1_SX300.jpg\",\"Ratings\":[{\"Source\":\"Internet Movie Database\",\"Value\":\"9.5/10\"}],\"Metascore\":\"N/A\",\"imdbRating\":\"9.5\",\"imdbVotes\":\"1,429,496\",\"imdbID\":\"tt0944947\",\"Type\":\"series\",\"totalSeasons\":\"8\",\"Response\":\"True\"}");
        emit requestComplete(200, data);
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

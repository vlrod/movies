#include <QtTest>
#include <QCoreApplication>
#include "omdbserviceapi.h"
#include "iwebrequest.h"
#include <iostream>
#include <memory>
#include "webrequestfake.hpp"
#include <QSignalSpy>
#include <QDebug>

class testOmdbServiceApi : public QObject
{
    Q_OBJECT

public:
    testOmdbServiceApi();

private slots:
    void testSearchValidname();
};

testOmdbServiceApi::testOmdbServiceApi()
{
}

void testOmdbServiceApi::testSearchValidname()
{
    std::shared_ptr<IWebRequest> i = std::make_shared<WebRequestFake>();
    std::unique_ptr<OmdbServiceApi> omdb(new OmdbServiceApi(i));
    QSignalSpy spy(omdb.get(), SIGNAL(searchComplete(int, const QByteArray&)));

    omdb->searchMovieByName("game");
    QCOMPARE(spy.count(), 1);

    QList<QVariant> arguments = spy.takeFirst();
    QVERIFY(arguments.at(0).toInt() == 200);

    QByteArray movieData = qvariant_cast<QByteArray>(arguments.at(1));
    auto json_doc = QJsonDocument::fromJson(movieData);
    QJsonObject json_obj = json_doc.object();
    QVariantMap movie = json_obj.toVariantMap();
    QCOMPARE(movie["Title"].toString(), QString("Game of Thrones"));
}

QTEST_MAIN(testOmdbServiceApi)

#include "tst_testomdbserviceapi.moc"

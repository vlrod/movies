#include <QtTest>
#include <QCoreApplication>
#include "omdbserviceapi.h"
#include "iwebrequest.h"
#include <iostream>
#include <memory>
#include "webrequestfake.hpp"

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
    omdb->searchMovieByName("game");
}

QTEST_MAIN(testOmdbServiceApi)

#include "tst_testomdbserviceapi.moc"

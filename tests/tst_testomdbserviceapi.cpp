#include <QtTest>
#include <QCoreApplication>
#include "omdbserviceapi.h"

// add necessary includes here

class testOmdbServiceApi : public QObject
{
    Q_OBJECT

public:
    testOmdbServiceApi();
    ~testOmdbServiceApi();

private slots:
    void test_case1();

};

testOmdbServiceApi::testOmdbServiceApi()
{
    OmdbServiceApi controller;
    controller.searchMovieByName("game");
}

testOmdbServiceApi::~testOmdbServiceApi()
{

}

void testOmdbServiceApi::test_case1()
{

}

QTEST_MAIN(testOmdbServiceApi)

#include "tst_testomdbserviceapi.moc"

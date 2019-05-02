#include <QtTest>
#include <QCoreApplication>

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

}

testOmdbServiceApi::~testOmdbServiceApi()
{

}

void testOmdbServiceApi::test_case1()
{

}

QTEST_MAIN(testOmdbServiceApi)

#include "tst_testomdbserviceapi.moc"

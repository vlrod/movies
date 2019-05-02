#ifndef MOVIESSEARCH_H
#define MOVIESSEARCH_H

#include <QCommandLineParser>
#include <QCommandLineOption>
#include <QString>
#include <QObject>
#include "omdbserviceapi.h"

class QCommandLineParser;

class MoviesSearch: public QObject
{
    Q_OBJECT
public:
    MoviesSearch(QCommandLineParser *parser);
    ~MoviesSearch();
    void runMain();

public slots:
    void onSearchComplete(int statusCode, const QByteArray& body);

private:
    QCommandLineParser *m_parser;
    QCommandLineOption* type;
    QCommandLineOption* search;
    OmdbServiceApi* controller;
};

#endif // MOVIESSEARCH_H

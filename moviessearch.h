#ifndef MOVIESSEARCH_H
#define MOVIESSEARCH_H

#include <QCommandLineParser>
#include <QCommandLineOption>
#include <QString>
#include "controller.h"

class QCommandLineParser;

class MoviesSearch
{
public:
    MoviesSearch(QCommandLineParser *parser);
    ~MoviesSearch();
    void runMain();

private:
    QCommandLineParser *m_parser;
    QCommandLineOption* type;
    QCommandLineOption* search;
    Controller* controller;
};

#endif // MOVIESSEARCH_H

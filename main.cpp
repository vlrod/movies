#include "moviessearch.h"
#include <QCoreApplication>
#include <QDebug>
#include <QCommandLineParser>
#include <QCommandLineOption>

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);
    QCoreApplication::setApplicationName("Movies Test");
    QCoreApplication::setApplicationVersion("1.0");

    QCommandLineParser parser;
    parser.setApplicationDescription("Search data of movies, series, etc");
    parser.addVersionOption();
    parser.addHelpOption();

    MoviesSearch movieSearch(&parser);

    parser.process(app);
    movieSearch.runMain();

    return app.exec();
}

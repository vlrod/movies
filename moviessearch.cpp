#include "moviessearch.h"

#include <QDebug>

MoviesSearch::MoviesSearch(QCommandLineParser *parser)
    : m_parser(parser)

{
    controller = new OmdbServiceApi();
    const static auto _s = QStringLiteral("search");
    const static auto _n = QStringLiteral("name");
    const static auto _t = QStringLiteral("type");
    const static auto _td = QStringLiteral("contentType");
    search = new QCommandLineOption(QStringList() << QStringLiteral("s") << _s,
                               QStringLiteral("Search for the content title"), _n);
    type = new QCommandLineOption(QStringList() << QStringLiteral("t") << _t,
                                QStringLiteral("Return only content with specified type"), _td);

    m_parser->addOption(*type);
    m_parser->addOption(*search);
}

void MoviesSearch::runMain()
{
    if (!m_parser->isSet(*search)) {
        m_parser->showHelp(1);
    }
    if (m_parser->isSet(*search)) {
        QString title = m_parser->value(*search);
        controller->searchMovieByName(title);
    }
    if (m_parser->isSet(*type)) {
        QString stype = m_parser->value(*type);
        qDebug() << "search title " << type << "\n";
    }
}


MoviesSearch::~MoviesSearch()
{
    delete controller;
    delete search;
    delete type;
}

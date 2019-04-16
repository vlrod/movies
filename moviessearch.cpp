#include "moviessearch.h"
#include <cstdlib>
#include <QDebug>

MoviesSearch::MoviesSearch(QCommandLineParser *parser)
    : m_parser(parser)
{
    controller = new OmdbServiceApi();
    const static auto _s = QStringLiteral("search");
    const static auto _n = QStringLiteral("name");
    const static auto _t = QStringLiteral("type");
    const static auto _ct = QStringLiteral("contentType");
    search = new QCommandLineOption(QStringList() << QStringLiteral("s") << _s,
                                    QStringLiteral("Search for the content title"), _n);
    type = new QCommandLineOption(QStringList() << QStringLiteral("t") << _t,
                                  QStringLiteral("Return only content with specified type"), _ct);
    m_parser->addOption(*type);
    m_parser->addOption(*search);
    QObject::connect(controller, &OmdbServiceApi::searchComplete, this, &MoviesSearch::onSearchComplete);
}

void MoviesSearch::runMain()
{
    if (!m_parser->isSet(*search)) {
        m_parser->showHelp(EXIT_FAILURE);
    }

    if (m_parser->isSet(*search) && m_parser->isSet(*type)) {
        QString title = m_parser->value(*search);
        QString stype = m_parser->value(*type);
        controller->searchMovieByNameAndType(title, stype);
    } else if (m_parser->isSet(*search)) {
        QString title = m_parser->value(*search);
        controller->searchMovieByName(title);
    }
}

void MoviesSearch::onSearchComplete(int statusCode, const QByteArray& body)
{
    qDebug() << "<MoviesSearch> Received response code " << statusCode << ":";
    qDebug() << body;
}

MoviesSearch::~MoviesSearch()
{
    delete controller;
    delete search;
    delete type;
}

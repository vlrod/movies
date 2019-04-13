#include <QCoreApplication>
#include <QDebug>
#include "controller.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Controller con;
    con.searchMovieByName("the+wolf");

    return a.exec();
}

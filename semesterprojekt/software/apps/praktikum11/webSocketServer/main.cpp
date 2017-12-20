#include <QtCore>

#include "chatserver.h"

int main(int argc, char* argv[])
{
    QCoreApplication app(argc, argv);

    ChatServer server;

    return app.exec();
}

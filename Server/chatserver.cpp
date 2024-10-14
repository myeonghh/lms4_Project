#include "chatserver.h"
#include <QRegularExpression>
#include <QRegularExpressionMatch>

ChatServer::ChatServer(QObject *parent)
    : QTcpServer(parent)
{
}

void ChatServer::incomingConnection(qintptr socketfd)
{
    QTcpSocket *client = new QTcpSocket(this);
    client->setSocketDescriptor(socketfd);
    clients.insert(client);

    emit clients_signal(clients.count());

    QString str;
    str = QString("New Member: %1")
            .arg(client->peerAddress().toString());

    emit message_signal(str);

    connect(client, SIGNAL(readyRead()), this,
                    SLOT(readyRead()));
    connect(client, SIGNAL(disconnected()), this,
                    SLOT(disconnected()));
}

void ChatServer::readyRead()
{
    QTcpSocket *client = (QTcpSocket*)sender();
    while(client->canReadLine())
    {
        QString line = QString::fromUtf8(client->readLine()).trimmed();

        QString str;
        str = QString("Read line: %1").arg(line);

        emit message_signal(str);

        QRegularExpression meRegex("^/me:(.*)$");
        QRegularExpressionMatch match = meRegex.match(line);

        if(match.hasMatch())
        {
            QString user = match.captured(1);
            users[client] = user;
            foreach(QTcpSocket *client, clients)
            {
                client->write(QString("Server: %1 connected\n")
                              .arg(user).toUtf8());
            }

            //sendUserList();
        }
        else if(users.contains(client))
        {
            QString message = line;
            QString user = users[client];

            QString str;
            str = QString("User name: %1, Message: %2")
                    .arg(user, message);
            emit message_signal(str);

            foreach(QTcpSocket *otherClient, clients)
                otherClient->write(QString(user+":"+message+"\n")
                                        .toUtf8());
        }
    }
}

void ChatServer::disconnected()
{
    QTcpSocket *client = (QTcpSocket*)sender();

    QString str;
    str = QString("Disconnect: %1")
            .arg(client->peerAddress().toString());

    emit message_signal(str);

    clients.remove(client);

    emit clients_signal(clients.count());

    QString user = users[client];
    users.remove(client);

    sendUserList();
    foreach(QTcpSocket *client, clients)
        client->write(QString("Server: %1 Disconnect").arg(user).toUtf8());
}

void ChatServer::sendUserList()
{
    QStringList userList;
    foreach(QString user, users.values())
        userList << user;

    foreach(QTcpSocket *client, clients)
        client->write(QString("User:" + userList.join(",") + "\n").toUtf8());
}


ChatServer::~ChatServer()
{
    deleteLater();
}

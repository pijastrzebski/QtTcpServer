#include "tcpServer.h"
#include <QDebug>

tcpServer::tcpServer(QWidget *parent)
    : QWidget(parent),
    m_serverView(new ServerView(this)),
    m_port(666)
{
    initServer();
}

void tcpServer::initServer()
{
    m_server = new QTcpServer(this);

    // basic connects
    connect(m_server, &QTcpServer::newConnection, [this]() {
        newConnection();
    });


    if (!m_server->listen(QHostAddress::Any, m_port))
    {
        qDebug() << "Server couldn't start";
    }
    else
    {
        qDebug() << "Server started at port: " << m_port;
    }

    // connects to view server
    connect(this, &tcpServer::onUpdateView, [this](const QString& title) { 
        m_serverView->updateView(title); 
    });
}

void tcpServer::newConnection()
{
    qDebug() << "New Connection Detected";
    QString newTitle = "Established connection at port: " + QString::number(m_port);
    emit onUpdateView(newTitle);

    m_socket = m_server->nextPendingConnection();
    
    connect(m_socket, &QTcpSocket::connected, [this]() {
        qDebug() << "Slot connected()";
    });
    connect(m_socket, &QTcpSocket::disconnected, [this]() {
        qDebug() << "Slot disconnected()";

    });
    connect(m_socket, &QTcpSocket::bytesWritten, [this](qint64 bytes) {
        qDebug() << "Slot bytesWritten(): " << QString::number(bytes);
    });
    connect(m_socket, &QTcpSocket::readyRead, [this]() {
        readyRead();
    });

    m_socket->write("Message from Server: Hello Client!\r\n");
    m_socket->flush();

    const int TIME_WAIT_MS = 3000;
    m_socket->waitForBytesWritten(TIME_WAIT_MS);

    //m_socket->close();
}

void tcpServer::readyRead()
{
    qDebug() << "Ready read slot";       
    qDebug() << "Server received the data: " << m_socket->readAll();

    m_socket->flush();
}

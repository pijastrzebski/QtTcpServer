#pragma once

#include <QtWidgets/QWidget>
#include <QTcpServer>
#include <QTcpSocket>

#include "ServerView.h"

// async tcp server 

class tcpServer : public QWidget
{
    Q_OBJECT

public:
    explicit tcpServer(QWidget *parent = Q_NULLPTR);


signals:
    void onUpdateView(const QString& title);

public slots:
    void initServer();
    void newConnection();
    

private:
    ServerView *m_serverView; //TODO: Add interface for the view class

    int m_port;
    QTcpServer *m_server;
    QTcpSocket *m_socket;

    void readyRead();
};

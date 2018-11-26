#include "ServerView.h"
#include <QApplication>
#include <QRect>
#include <QScreen>

ServerView::ServerView(QWidget *parent)
    : QDialog(parent)
{
    int dialogWidth = 400;
    int dialogHeight = 100;
    resize(dialogWidth, dialogHeight);
    QScreen *screen = QGuiApplication::primaryScreen();
    QRect screenGeo = screen->geometry();
    auto width = screenGeo.width();
    auto height = screenGeo.height();
    move(0, 0);
    move(width/2 - dialogWidth /2, height/2 - dialogHeight /2);
    setWindowTitle("Tcp Server");
    
    show();
}

void ServerView::updateView(const QString& title)
{
    setWindowTitle(title);
    update();
}


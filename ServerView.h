#pragma once

#include <QDialog>

class ServerView : public QDialog
{
    Q_OBJECT

public:
    explicit ServerView(QWidget *parent = Q_NULLPTR);

public slots:
    void updateView(const QString& title);

private:
};

#pragma once

#include <QMainWindow>

class MainScalableWidget;

class HeavensStdout : public QMainWindow
{
    Q_OBJECT
public:
    explicit HeavensStdout(QWidget *parent = nullptr);

private:
    MainScalableWidget *mCentralWidget = nullptr;
};

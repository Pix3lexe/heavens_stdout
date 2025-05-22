#pragma once
#include "mainScalableWidget.h"

#include <QMainWindow>

class HeavensStdout : public QMainWindow
{
    Q_OBJECT
public:
    explicit HeavensStdout(QWidget *parent = nullptr);

private:
    MainScalableWidget *mCentralWidget = nullptr;
};

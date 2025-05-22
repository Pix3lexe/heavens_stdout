#include "heavens_stdout.h"

#include "mainScalableWidget.h"

HeavensStdout::HeavensStdout(QWidget *parent) : QMainWindow(parent)
{
    mCentralWidget = new MainScalableWidget(this);
    setCentralWidget(mCentralWidget);
}

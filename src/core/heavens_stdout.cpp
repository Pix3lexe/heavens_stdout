#include "heavens_stdout.h"

HeavensStdout::HeavensStdout(QWidget *parent) : QMainWindow(parent)
{
    mCentralWidget = new MainScalableWidget(this);
    setCentralWidget(mCentralWidget);
}

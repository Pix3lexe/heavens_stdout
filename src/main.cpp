#include "heavensstdout.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication  app(argc, argv);
    HeavensStdout heavensStdout;
    heavensStdout.show();
    return app.exec();
}

#pragma once

#include "generator.h"
#include "ui_heavensstdout.h"

#include <QMainWindow>


class HeavensStdout : public QMainWindow
{
    Q_OBJECT
public:
    explicit HeavensStdout(QWidget *parent = nullptr);

public slots:
    void onTalkButtonClicked();

private:
    Ui::MainWindow mUi;
    Generator      mGenerator;
};

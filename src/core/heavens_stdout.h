#pragma once

#include "stringSearchModeWidget.h"
#include "talkModeWidget.h"
#include "ui_heavens_stdout.h"

#include <QMainWindow>
#include <QTimer>


class HeavensStdout : public QMainWindow
{
    Q_OBJECT
public:
    explicit HeavensStdout(QWidget *parent = nullptr);

public slots:
    void onTalkModeButtonClicked();
    void onStringSearchModeButtonClicked();

private:
    Ui::MainWindow          mUi;
    TalkModeWidget         *mTalkModeWidget         = nullptr;
    StringSearchModeWidget *mStringSearchModeWidget = nullptr;
};

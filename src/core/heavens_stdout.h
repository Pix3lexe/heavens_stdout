#pragma once

#include "generator.h"
#include "ui_heavens_stdout.h"

#include <QMainWindow>
#include <QTimer>


constexpr int TYPING_SPEED = 50; // chars per second
class HeavensStdout : public QMainWindow
{
    Q_OBJECT
public:
    explicit HeavensStdout(QWidget *parent = nullptr);

public slots:
    void onSearchModeButtonClicked();
    void onTalkModeButtonClicked();
    void onTalkButtonClicked();
    void appendNextCharacter();

private:
    Ui::MainWindow mUi;
    Generator      mGenerator;
    QString        mFullText;
    int            mCurrentCharIndex = 0;
    QTimer         mTypingTimer;
};

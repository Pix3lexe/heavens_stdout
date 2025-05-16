#include "heavens_stdout.h"

HeavensStdout::HeavensStdout(QWidget *parent) : QMainWindow(parent)
{
    mUi.setupUi(this);
    connect(mUi.talkButton, &QPushButton::clicked, this, &HeavensStdout::onTalkButtonClicked);
    connect(&mTypingTimer, &QTimer::timeout, this, &HeavensStdout::appendNextCharacter);
}

void HeavensStdout::onTalkButtonClicked()
{
    mFullText         = mGenerator.generate_random_sentence();
    mCurrentCharIndex = 0;
    mUi.godLineEdit->clear();
    mTypingTimer.start(1000 / TYPING_SPEED);
}

void HeavensStdout::appendNextCharacter()
{
    if(mCurrentCharIndex < mFullText.length())
    {
        mUi.godLineEdit->insertPlainText(QString(mFullText[mCurrentCharIndex++]));
    }
    else
    {
        mTypingTimer.stop();
    }
}

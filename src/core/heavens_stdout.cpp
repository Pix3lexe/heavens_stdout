#include "heavens_stdout.h"

HeavensStdout::HeavensStdout(QWidget *parent) : QMainWindow(parent)
{
    mUi.setupUi(this);
    mUi.stringSearchLineEdit->setVisible(false);
    connect(mUi.searchModeButton, &QPushButton::clicked, this, &HeavensStdout::onSearchModeButtonClicked);
    connect(mUi.talkModeButton, &QPushButton::clicked, this, &HeavensStdout::onTalkModeButtonClicked);
    connect(mUi.talkButton, &QPushButton::clicked, this, &HeavensStdout::onTalkButtonClicked);
    connect(&mTypingTimer, &QTimer::timeout, this, &HeavensStdout::appendNextCharacter);
}

void HeavensStdout::onSearchModeButtonClicked()
{
    mUi.godLineEdit->clear();
    mUi.talkButton->setEnabled(false);
    mUi.talkButton->setVisible(false);
    mUi.stringSearchLineEdit->setEnabled(true);
    mUi.stringSearchLineEdit->setVisible(true);
}

void HeavensStdout::onTalkModeButtonClicked()
{
    mUi.godLineEdit->clear();
    mUi.stringSearchLineEdit->setEnabled(false);
    mUi.stringSearchLineEdit->setVisible(false);
    mUi.talkButton->setEnabled(true);
    mUi.talkButton->setVisible(true);
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

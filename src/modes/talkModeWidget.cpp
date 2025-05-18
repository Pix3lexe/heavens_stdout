#include "talkModeWidget.h"

TalkModeWidget::TalkModeWidget(QWidget *parent) : QWidget(parent)
{
    mUi.setupUi(this);
    connect(mUi.talkButton, &QPushButton::clicked, this, &TalkModeWidget::onTalkButtonClicked);
    connect(&mTypingTimer, &QTimer::timeout, this, &TalkModeWidget::appendNextCharacter);
}

void TalkModeWidget::onTalkButtonClicked()
{
    mFullText         = mGenerator.generateRandomSentence();
    mCurrentCharIndex = 0;
    mUi.godTextBrowserTalkMode->clear();
    mTypingTimer.start(1000 / TYPING_SPEED);
}

void TalkModeWidget::appendNextCharacter()
{
    if(mCurrentCharIndex < mFullText.length())
    {
        mUi.godTextBrowserTalkMode->insertPlainText(QString(mFullText[mCurrentCharIndex++]));
    }
    else
    {
        mTypingTimer.stop();
    }
}

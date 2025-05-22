#include "talkModeWidget.h"

TalkModeWidget::TalkModeWidget(QWidget *parent) : ScalableWidget(":resources/temple_bg_cropped.png", parent)
{
    mUi.setupUi(this);
    registerScalableChild(mUi.talkButton);
    registerScalableChild(mUi.godTextBrowserTalkMode);
    connect(mUi.talkButton, &QPushButton::clicked, this, &TalkModeWidget::onTalkButtonClicked);
    connect(&mTypingTimer, &QTimer::timeout, this, &TalkModeWidget::appendNextCharacter);
}

void TalkModeWidget::onTalkButtonClicked()
{
    mFullText         = mGenerator.generateRandomSentences();
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

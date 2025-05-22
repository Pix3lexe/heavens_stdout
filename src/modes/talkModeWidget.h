#pragma once

#include "generator.h"
#include "scalableWidget.h"
#include "ui_talkModeWidget.h"

#include <QTimer>

constexpr int TYPING_SPEED = 50; // chars per second

class TalkModeWidget : public ScalableWidget
{
    Q_OBJECT

public:
    explicit TalkModeWidget(QWidget *parent = nullptr);

public slots:
    void onTalkButtonClicked();
    void appendNextCharacter();

private:
    Ui::TalkModeWidget mUi;
    Generator          mGenerator;
    QString            mFullText;
    int                mCurrentCharIndex = 0;
    QTimer             mTypingTimer;
};

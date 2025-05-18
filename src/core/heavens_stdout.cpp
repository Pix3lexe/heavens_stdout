#include "heavens_stdout.h"

HeavensStdout::HeavensStdout(QWidget *parent) : QMainWindow(parent)
{
    mUi.setupUi(this);
    mTalkModeWidget         = new TalkModeWidget(this);
    mStringSearchModeWidget = new StringSearchModeWidget(this);
    mUi.widgetStack->addWidget(mTalkModeWidget);
    mUi.widgetStack->addWidget(mStringSearchModeWidget);

    connect(mUi.talkModeButton, &QPushButton::clicked, this, &HeavensStdout::onTalkModeButtonClicked);
    connect(mUi.stringSearchModeButton, &QPushButton::clicked, this, &HeavensStdout::onStringSearchModeButtonClicked);
}


void HeavensStdout::onTalkModeButtonClicked()
{
    mUi.widgetStack->setCurrentWidget(mTalkModeWidget);
}

void HeavensStdout::onStringSearchModeButtonClicked()
{
    mUi.widgetStack->setCurrentWidget(mStringSearchModeWidget);
}

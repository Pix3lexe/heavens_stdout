#include "mainScalableWidget.h"

#include "stringSearchModeWidget.h"
#include "talkModeWidget.h"

MainScalableWidget::MainScalableWidget(QWidget *parent) : ScalableWidget(":resources/temple_bg_cropped.png", parent)
{
    mUi.setupUi(this);
    mTalkModeWidget         = new TalkModeWidget(this);
    mStringSearchModeWidget = new StringSearchModeWidget(this);
    registerScalableChild(mUi.talkModeButton);
    registerScalableChild(mUi.stringSearchModeButton);
    registerScalableChild(mUi.widgetStack);
    registerScalableChild(mTalkModeWidget);
    registerScalableChild(mStringSearchModeWidget);

    mUi.widgetStack->addWidget(mTalkModeWidget);
    mUi.widgetStack->addWidget(mStringSearchModeWidget);

    connect(mUi.talkModeButton, &QPushButton::clicked, this, &MainScalableWidget::onTalkModeButtonClicked);
    connect(
        mUi.stringSearchModeButton, &QPushButton::clicked, this, &MainScalableWidget::onStringSearchModeButtonClicked);
}

void MainScalableWidget::onTalkModeButtonClicked()
{
    mUi.widgetStack->setCurrentWidget(mTalkModeWidget);
}

void MainScalableWidget::onStringSearchModeButtonClicked()
{
    mUi.widgetStack->setCurrentWidget(mStringSearchModeWidget);
}

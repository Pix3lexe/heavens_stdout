#pragma once

#include "scalableWidget.h"
#include "stringSearchModeWidget.h"
#include "talkModeWidget.h"
#include "ui_main_widget.h"

class MainScalableWidget : public ScalableWidget
{
    Q_OBJECT
public:
    explicit MainScalableWidget(QWidget *parent = nullptr);

private slots:
    void onTalkModeButtonClicked();
    void onStringSearchModeButtonClicked();

private:
    MainScalableWidget     *mCentralWidget          = nullptr;
    TalkModeWidget         *mTalkModeWidget         = nullptr;
    StringSearchModeWidget *mStringSearchModeWidget = nullptr;
    Ui::HeavensStdoutWidget mUi;
};

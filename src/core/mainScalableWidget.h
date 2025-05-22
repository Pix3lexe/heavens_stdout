#pragma once

#include "scalableWidget.h"
#include "ui_main_widget.h"

class TalkModeWidget;
class StringSearchModeWidget;

class MainScalableWidget : public ScalableWidget
{
    Q_OBJECT
public:
    explicit MainScalableWidget(QWidget *parent = nullptr);

private slots:
    void onTalkModeButtonClicked();
    void onStringSearchModeButtonClicked();

private:
    TalkModeWidget         *mTalkModeWidget         = nullptr;
    StringSearchModeWidget *mStringSearchModeWidget = nullptr;
    Ui::HeavensStdoutWidget mUi;
};

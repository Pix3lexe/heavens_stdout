#pragma once

#include "generator.h"
#include "ui_stringSearchModeWidget.h"

#include <QWidget>
class StringSearchModeWidget : public QWidget
{
    Q_OBJECT

public:
    explicit StringSearchModeWidget(QWidget *parent = nullptr);

public slots:
    void onStringSearchLineEditReturnPressed();

private:
    Ui::StringSearchModeWidget mUi;
    Generator                  mGenerator;
};

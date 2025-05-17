#pragma once

#include "ui_stringSearchModeWidget.h"

#include <QWidget>
class StringSearchModeWidget : public QWidget
{
    Q_OBJECT

public:
    explicit StringSearchModeWidget(QWidget *parent = nullptr);

public slots:

private:
    Ui::StringSearchModeWidget mUi;
};

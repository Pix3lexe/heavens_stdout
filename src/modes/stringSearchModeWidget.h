#pragma once

#include "ui_stringSearchModeWidget.h"

#include <QWidget>
#include <tuple>

class StringSearchModeWidget : public QWidget
{
    Q_OBJECT

public:
    explicit StringSearchModeWidget(QWidget *parent = nullptr);
    std::tuple<QString, int, std::size_t> searchString(const QString &search) const;
    QString                               generateSequenceAt(std::size_t position, int length) const;

public slots:
    void onStringSearchLineEditReturnPressed();

private:
    char getLetterAtPosition(std::size_t position, quint32 baseSeed) const;

    Ui::StringSearchModeWidget mUi;
    mutable quint32            mCurrentBaseSeed;
};

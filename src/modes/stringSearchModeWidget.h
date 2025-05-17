#pragma once

#include "ui_stringSearchModeWidget.h"

#include <QFutureWatcher>
#include <QWidget>
#include <tuple>

class StringSearchModeWidget : public QWidget
{
    Q_OBJECT

public:
    explicit StringSearchModeWidget(QWidget *parent = nullptr);
    ~StringSearchModeWidget();
    std::tuple<QString, int, std::size_t> searchString(const QString &search) const;
    QString                               generateSequenceAt(std::size_t position, int length) const;

public slots:
    void onStringSearchLineEditReturnPressed();
    void onSearchFinished();

private:
    char getLetterAtPosition(std::size_t position, quint32 baseSeed) const;

    Ui::StringSearchModeWidget                            mUi;
    mutable quint32                                       mCurrentBaseSeed;
    QString                                               mSearchString;
    QFutureWatcher<std::tuple<QString, int, std::size_t>> mSearchWatcher;
    bool                                                  mCancelFlag = false;
};

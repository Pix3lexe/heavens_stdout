#pragma once

#include "constants.h"
#include "scalableWidget.h"
#include "ui_stringSearchModeWidget.h"

#include <QFutureWatcher>
#include <string>
#include <tuple>

class StringSearchModeWidget : public ScalableWidget
{
    Q_OBJECT

public:
    explicit StringSearchModeWidget(QWidget *parent = nullptr);
    ~StringSearchModeWidget();
    void                                  startParallelSearch(const std::string &search);
    std::tuple<QString, int, std::size_t> searchString(const std::string &search) const;
    QString                               generateSequenceAt(std::size_t position, int length, quint64 seed) const;

public slots:
    void onStringSearchLineEditReturnPressed();
    void onSearchFinished();

private:
    inline char getLetterAtPosition(std::size_t position, quint64 baseSeed) const noexcept
    {
        quint64 seed = baseSeed + position;

        // This is a simplified version of MurmurHash3 mixing
        seed ^= seed >> 33;
        seed *= 0xff51afd7ed558ccdULL;
        seed ^= seed >> 33;
        seed *= 0xc4ceb9fe1a85ec53ULL;
        seed ^= seed >> 33;

        return LETTERS[seed % LETTER_COUNT];
    }

    Ui::StringSearchModeWidget                            mUi;
    std::string                                           mSearchString;
    QFutureWatcher<std::tuple<QString, int, std::size_t>> mSearchWatcher;
    bool                                                  mCancelFlag = false;
};

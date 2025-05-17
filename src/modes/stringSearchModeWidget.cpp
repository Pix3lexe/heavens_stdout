#include "stringSearchModeWidget.h"

#include "constants.h"

#include <QFutureWatcher>
#include <QtConcurrent/QtConcurrent>

StringSearchModeWidget::StringSearchModeWidget(QWidget *parent) : QWidget(parent), mCurrentBaseSeed(1)
{
    mUi.setupUi(this);

    connect(
        mUi.stringSearchLineEdit,
        &QLineEdit::returnPressed,
        this,
        &StringSearchModeWidget::onStringSearchLineEditReturnPressed);
}

void StringSearchModeWidget::onStringSearchLineEditReturnPressed()
{
    mUi.godTextBrowserSearchMode->clear();
    QString searchString = mUi.stringSearchLineEdit->text().toLower().remove(' ');
    mUi.stringSearchLineEdit->clear();
    mUi.godTextBrowserSearchMode->setText("Searching in gods messages...");

    auto watcher = new QFutureWatcher<std::tuple<QString, int, std::size_t>>(this);

    connect(
        watcher,
        &QFutureWatcher<std::tuple<QString, int, std::size_t>>::finished,
        this,
        [=, this]()
        {
            auto [context, localIndex, globalIndex] = watcher->result();
            QString before                          = context.left(localIndex);
            QString match                           = context.mid(localIndex, searchString.length());
            QString after                           = context.mid(localIndex + searchString.length());

            QString displayText =
                QString("%1<span style=\"color: red; font-weight: bold;\">%2</span>%3").arg(before, match, after);
            mUi.godTextBrowserSearchMode->setHtml(displayText);

            mUi.stringSearchLineEdit->setText(QString("Found after %1 letters").arg(globalIndex));
            watcher->deleteLater();
        });

    QFuture<std::tuple<QString, int, std::size_t>> future =
        QtConcurrent::run([=, this]() { return this->searchString(searchString); });

    watcher->setFuture(future);
}


QVector<int> prefixFunction(const QString &pattern)
{
    int          n = pattern.length();
    QVector<int> pi(n, 0);
    int          k = 0;
    for(int i = 1; i < n; ++i)
    {
        while(k > 0 && pattern[k] != pattern[i])
            k = pi[k - 1];
        if(pattern[k] == pattern[i])
            ++k;
        pi[i] = k;
    }
    return pi;
}

std::tuple<QString, int, std::size_t> StringSearchModeWidget::searchString(const QString &search) const
{
    std::size_t position  = 0;
    int         searchInd = 0;
    int         searchLen = search.length();
    mCurrentBaseSeed      = QRandomGenerator::global()->generate();

    auto pi = prefixFunction(search);
    while(searchInd < searchLen)
    {
        char nextLetter = getLetterAtPosition(position, mCurrentBaseSeed);
        while(searchInd > 0 && nextLetter != search.at(searchInd))
        {
            searchInd = pi[searchInd - 1];
        }
        if(nextLetter == search.at(searchInd))
        {
            ++searchInd;
        }
        ++position;
    }


    std::size_t foundPosition = position - searchLen;
    const int   contextSize   = 100;
    int         beforeStart   = static_cast<int>(foundPosition) - contextSize;
    if(beforeStart < 0)
    {
        beforeStart = 0;
    }

    QString result     = generateSequenceAt(beforeStart, foundPosition - beforeStart + searchLen + contextSize);
    int     localIndex = static_cast<int>(foundPosition - beforeStart);

    return std::make_tuple(result, localIndex, foundPosition);
}

QString StringSearchModeWidget::generateSequenceAt(std::size_t position, int length) const
{
    QString result;
    result.reserve(length);

    for(int i = 0; i < length; ++i)
    {
        result.append(getLetterAtPosition(position + i, mCurrentBaseSeed));
    }

    return result;
}

char StringSearchModeWidget::getLetterAtPosition(std::size_t position, quint32 baseSeed) const
{
    quint32 seed = baseSeed + position;

    // This is a simplified version of MurmurHash3 mixing
    seed ^= seed >> 16;
    seed *= 0x85ebca6b;
    seed ^= seed >> 13;
    seed *= 0xc2b2ae35;
    seed ^= seed >> 16;

    int index = seed % LETTERS.size();
    return LETTERS[index];
}

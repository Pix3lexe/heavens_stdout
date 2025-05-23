#include "stringSearchModeWidget.h"

#include <QFutureWatcher>
#include <QtConcurrent/QtConcurrent>
#include <vector>

StringSearchModeWidget::StringSearchModeWidget(QWidget *parent) : QWidget(parent)
{
    mUi.setupUi(this);

    connect(
        mUi.stringSearchLineEdit,
        &QLineEdit::returnPressed,
        this,
        &StringSearchModeWidget::onStringSearchLineEditReturnPressed);
    connect(
        &mSearchWatcher,
        &QFutureWatcher<std::tuple<QString, int, std::size_t>>::finished,
        this,
        &StringSearchModeWidget::onSearchFinished);
}

StringSearchModeWidget::~StringSearchModeWidget()
{
    mCancelFlag = true;
}

void StringSearchModeWidget::onStringSearchLineEditReturnPressed()
{
    mUi.godTextBrowserSearchMode->clear();
    mSearchString = mUi.stringSearchLineEdit->text().toLower().remove(' ').toStdString();
    mUi.stringSearchLineEdit->clear();
    mUi.godTextBrowserSearchMode->setText("Searching in gods messages...");
    startParallelSearch(mSearchString);
}

void StringSearchModeWidget::onSearchFinished()
{
    auto [context, localIndex, globalIndex] = mSearchWatcher.result();
    if(localIndex == -1)
    {
        return;
    }
    QString before = context.left(localIndex);
    QString match  = context.mid(localIndex, mSearchString.length());
    QString after  = context.mid(localIndex + mSearchString.length());

    QString displayText =
        QString("...%1<span style=\"color: red; font-weight: bold;\">%2</span>%3...").arg(before, match, after);
    mUi.godTextBrowserSearchMode->setHtml(displayText);

    mUi.godTextBrowserSearchMode->append(
        QString("<span style=\"color: green; font-weight: bold;\">Found after %1 letters</span>").arg(globalIndex));
}


inline std::vector<int> prefixFunction(const std::string &pattern)
{
    const int        n = pattern.length();
    std::vector<int> pi(n);
    int              k = 0;
    for(int i = 1; i < n; ++i)
    {
        while(k > 0 && pattern[k] != pattern[i])
        {
            k = pi[k - 1];
        }
        if(pattern[k] == pattern[i])
        {
            ++k;
        }
        pi[i] = k;
    }
    return pi;
}

inline void generateBlock(char *buffer, std::size_t startPos, int length, quint64 baseSeed) noexcept
{
    constexpr int BLOCK_SIZE = 64; // Process in blocks

    for(int i = 0; i < length; i += BLOCK_SIZE)
    {
        const int blockEnd = std::min(i + BLOCK_SIZE, length);
        for(int j = i; j < blockEnd; ++j)
        {
            quint64 seed = baseSeed + startPos + j;
            seed ^= seed >> 33;
            seed *= 0xff51afd7ed558ccdULL;
            seed ^= seed >> 33;
            buffer[j] = LETTERS[seed % LETTER_COUNT];
        }
    }
}

std::tuple<QString, int, std::size_t> StringSearchModeWidget::searchString(const std::string &search) const
{
    if(search.empty())
        return {"", -1, 0};

    std::size_t   position  = 0;
    int           searchInd = 0;
    const int     searchLen = search.length();
    const quint64 seed      = QRandomGenerator64::global()->generate();

    const auto pi = prefixFunction(search);

    constexpr int BUFFER_SIZE = 1024;
    char          buffer[BUFFER_SIZE];
    int           bufferPos = BUFFER_SIZE;

    while(searchInd < searchLen && !mCancelFlag)
    {
        // Refill buffer when needed
        if(bufferPos >= BUFFER_SIZE)
        {
            generateBlock(buffer, position, BUFFER_SIZE, seed);
            bufferPos = 0;
        }

        const char nextLetter = buffer[bufferPos++];
        const char targetChar = search[searchInd];

        // KMP matching
        while(searchInd > 0 && nextLetter != search[searchInd])
        {
            searchInd = pi[searchInd - 1];
        }

        if(nextLetter == targetChar)
        {
            ++searchInd;
        }

        ++position;
    }

    if(mCancelFlag)
    {
        return {"", -1, 0};
    }

    const std::size_t foundPosition = position - searchLen;
    constexpr int     contextSize   = 100;
    const int         beforeStart   = std::max(0, static_cast<int>(foundPosition) - contextSize);

    const QString result = generateSequenceAt(beforeStart, foundPosition - beforeStart + searchLen + contextSize, seed);
    const int     localIndex = static_cast<int>(foundPosition - beforeStart);

    return std::make_tuple(result, localIndex, foundPosition);
}

QString StringSearchModeWidget::generateSequenceAt(std::size_t position, int length, quint64 seed) const
{
    QString result;
    result.reserve(length);

    for(int i = 0; i < length; ++i)
    {
        result.append(getLetterAtPosition(position + i, seed));
    }

    return result;
}

void StringSearchModeWidget::startParallelSearch(const std::string &search)
{
    if(mSearchWatcher.isRunning())
    {
        mCancelFlag = true;
        mSearchWatcher.waitForFinished();
    }
    mCancelFlag = false;

    const int threadCount = std::thread::hardware_concurrency();

    QList<QFuture<std::tuple<QString, int, std::size_t>>> futures;

    // start parallel searches
    for(int i = 0; i < threadCount; ++i)
    {
        QFuture<std::tuple<QString, int, std::size_t>> future =
            QtConcurrent::run([this, search]() { return this->searchString(search); });

        futures.append(future);
    }

    // master future that checks all ongoing searches
    QFuture<std::tuple<QString, int, std::size_t>> masterFuture = QtConcurrent::run(
        [this, futures]()
        {
            while(!mCancelFlag)
            {
                for(const auto &future : futures)
                {
                    if(future.isFinished())
                    {
                        auto result = future.result();

                        if(!std::get<0>(result).isEmpty())
                        {
                            mCancelFlag = true;
                            return result;
                        }
                    }
                }

                bool allDone = true;
                for(const auto &future : futures)
                {
                    if(!future.isFinished())
                    {
                        allDone = false;
                        break;
                    }
                }

                if(allDone)
                {
                    return std::tuple<QString, int, std::size_t>{QString(), 0, 0};
                }
            }

            return std::tuple<QString, int, std::size_t>{QString(), 0, 0};
        });

    mSearchWatcher.setFuture(masterFuture);
}

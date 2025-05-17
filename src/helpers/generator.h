#pragma once
#include <QHash>
#include <QList>
#include <QRandomGenerator>
#include <QString>
#include <QStringList>
#include <cstddef>
#include <optional>
#include <utility>

enum Complexity
{
    LOW,
    NORMAL,
    HIGH,
    GENIOUS,
    COMPLEXITY_COUNT
};

enum WordType
{
    NOUN,
    VERB,
    ADJECTIVE,
    ADVERB,
    PRONOUN,
    PREPOSITION,
    CONJUNCTION,
    DETERMINER,
    INTERJECTION,
    END,
    WT_COUNT
};


class Generator
{
public:
    Generator();
    QString generateSentence(Complexity complexity) const;
    QString generateRandomSentence() const;

    std::pair<QString, std::size_t> searchString(const QString &search) const;
    QString                         generateSequenceAt(std::size_t position, int length) const;

    const QString getWordsOfType(WordType type) const
    {
        if(mWordMap.contains(type))
        {
            return mWordMap[type].join(' ');
        }
        return "";
    }

private:
    std::optional<WordType> mapSpeechPart(const QString &part) const;

    void    loadWordsetJson(const QString &directoryPath);
    QString pickRandomWord(const QStringList &wordList) const;
    bool    dfs(WordType curType, int wordCount, QString &currentSentence, const std::uint16_t maxWords) const;

    char getLetterAtPosition(std::size_t position, quint32 baseSeed) const;

    template <typename T, std::size_t N>
    const T &getRandomArrayElem(const std::array<T, N> &array) const
    {
        int index = QRandomGenerator::global()->bounded(static_cast<quint32>(array.size()));
        return array[index];
    }

private:
    QHash<WordType, QStringList> mWordMap;
    mutable quint32              mCurrentBaseSeed;
};

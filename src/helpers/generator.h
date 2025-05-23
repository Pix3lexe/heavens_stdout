#pragma once
#include <QHash>
#include <QList>
#include <QRandomGenerator>
#include <QString>
#include <QStringList>
#include <cstddef>
#include <optional>

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
    QString generateRandomSentences() const;

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


    template <typename T, std::size_t N>
    const T &getRandomArrayElem(const std::array<T, N> &array) const
    {
        int index = QRandomGenerator::global()->bounded(static_cast<quint32>(array.size()));
        return array[index];
    }

    static constexpr int MAX_SENTENCES = 5;

private:
    QHash<WordType, QStringList> mWordMap;
};

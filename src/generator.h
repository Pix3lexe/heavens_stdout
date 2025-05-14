#pragma once
#include <QHash>
#include <QList>
#include <QString>
#include <QStringList>
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
    QString generate_sentence(Complexity complexity);

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

private:
    QHash<WordType, QStringList> mWordMap;
};

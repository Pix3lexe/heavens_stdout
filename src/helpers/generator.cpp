#include "generator.h"

#include "constants.h"

#include <QDir>
#include <QJsonArray>
#include <QJsonObject>
#include <QRandomGenerator>
#include <QVector>
#include <cstdint>

Generator::Generator() : mCurrentBaseSeed(1)
{
    loadWordsetJson("../deps/wordset-dictionary/data");
}

QString Generator::pickRandomWord(const QStringList &wordList) const
{
    if(wordList.isEmpty())
    {
        return {};
    }
    int index = QRandomGenerator::global()->bounded(wordList.length());
    return wordList.at(index);
}

QString Generator::generateSentence(Complexity complexity) const
{
    std::uint16_t maxWords = SENTENCE_LENGTHS[complexity];
    QString       sentence{};
    WordType      startType = getRandomArrayElem(START_RULES);
    if(dfs(startType, 0, sentence, maxWords))
    {
        return sentence.removeFirst();
    }

    return "No valid sentence found :/";
}

QString Generator::generateRandomSentence() const
{
    return generateSentence(getRandomArrayElem(COMPLEXITIES));
}


bool Generator::dfs(WordType curType, int wordCount, QString &currentSentence, const std::uint16_t maxWords) const
{
    if(wordCount == maxWords)
    {
        if(curType == WordType::END)
        {
            currentSentence.append(".");
            return true;
        }
        return false;
    }
    currentSentence.append(" " + pickRandomWord(mWordMap[curType]));
    ++wordCount;

    for(WordType nextType : FOLLOW_RULES[curType])
    {
        if(nextType != WordType::WT_COUNT)
        {
            QString backupSentence = currentSentence;

            if(dfs(nextType, wordCount, currentSentence, maxWords))
            {
                return true;
            }
            currentSentence = backupSentence;
        }
    }

    return false; // No valid path found from here
}

std::optional<WordType> Generator::mapSpeechPart(const QString &part) const
{
    if(part == "noun")
        return WordType::NOUN;
    if(part == "verb")
        return WordType::VERB;
    if(part == "adjective")
        return WordType::ADJECTIVE;
    if(part == "adverb")
        return WordType::ADVERB;
    if(part == "pronoun")
        return WordType::PRONOUN;
    if(part == "preposition")
        return WordType::PREPOSITION;
    if(part == "conjunction")
        return WordType::CONJUNCTION;
    if(part == "determiner")
        return WordType::DETERMINER;
    if(part == "interjection")
        return WordType::INTERJECTION;
    return std::nullopt;
}


void Generator::loadWordsetJson(const QString &directoryPath)
{
    QDir        dir(directoryPath);
    QStringList files = dir.entryList(QStringList() << "*.json", QDir::Files);

    for(const QString &fileName : files)
    {
        QFile file(dir.filePath(fileName));
        if(!file.open(QIODevice::ReadOnly))
            continue;

        QJsonParseError err;
        QJsonDocument   doc = QJsonDocument::fromJson(file.readAll(), &err);
        if(err.error != QJsonParseError::NoError || !doc.isObject())
            continue;

        QJsonObject root = doc.object();
        for(const QString &key : root.keys())
        {
            QJsonObject entry    = root[key].toObject();
            QString     word     = entry["word"].toString();
            QJsonArray  meanings = entry["meanings"].toArray();

            for(const QJsonValue &val : meanings)
            {
                QJsonObject meaning = val.toObject();
                QString     part    = meaning["speech_part"].toString().toLower();

                if(auto type = mapSpeechPart(part))
                {
                    mWordMap[*type].append(word);
                    break; // only need it once per word
                }
            }
        }
    }
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

std::tuple<QString, int, std::size_t> Generator::searchString(const QString &search) const
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

QString Generator::generateSequenceAt(std::size_t position, int length) const
{
    QString result;
    result.reserve(length);

    for(int i = 0; i < length; ++i)
    {
        result.append(getLetterAtPosition(position + i, mCurrentBaseSeed));
    }

    return result;
}

char Generator::getLetterAtPosition(std::size_t position, quint32 baseSeed) const
{
    quint32 seed = baseSeed + position;

    // Apply a better mixing function for the seed
    // This is a simplified version of MurmurHash3 mixing
    seed ^= seed >> 16;
    seed *= 0x85ebca6b;
    seed ^= seed >> 13;
    seed *= 0xc2b2ae35;
    seed ^= seed >> 16;

    // Convert to index in the LETTERS array
    int index = seed % LETTERS.size();
    return LETTERS[index];
}

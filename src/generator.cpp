#include "generator.h"

#include "constants.h"

#include <QDir>
#include <QJsonArray>
#include <QJsonObject>
#include <QRandomGenerator>
#include <cstdint>
#include <qlogging.h>

Generator::Generator()
{
    loadWordsetJson("../deps/wordset-dictionary/data");
}

QString Generator::pickRandomWord(const QStringList &wordList) const
{
    int index = QRandomGenerator::global()->bounded(wordList.length());
    return wordList.at(index);
}

QString Generator::generate_sentence(Complexity complexity)
{
    std::uint16_t maxWords  = SENTENCE_LENGTHS[complexity];
    int           wordCount = QRandomGenerator::global()->bounded(maxWords);
    QString       sentence{};
    for(int i = 0; i < wordCount; ++i)
    {
        sentence.append(" " + pickRandomWord(mWordMap[WordType::NOUN]));
    }
    return sentence;
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

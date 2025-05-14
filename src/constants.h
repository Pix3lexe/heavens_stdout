#pragma once
#include "generator.h"

#include <array>
#include <cstdint>

constexpr std::array<std::uint16_t, COMPLEXITY_COUNT> SENTENCE_LENGTHS = {5, 7, 10, 14};
constexpr std::uint8_t                                MAX_FOLLOW       = 5;

using FollowList = std::array<WordType, MAX_FOLLOW>;

constexpr std::array<WordType, 5> START_RULES =
    {WordType::NOUN, WordType::PRONOUN, WordType::DETERMINER, WordType::INTERJECTION, WordType::ADJECTIVE};


// word types that can follow after another word
constexpr std::array<FollowList, WT_COUNT> FOLLOW_RULES = {
    {// WordType::NOUN
     {WordType::VERB, WordType::CONJUNCTION, WordType::PREPOSITION, WordType::END, WordType::WT_COUNT},

     // WordType::VERB
     {WordType::NOUN, WordType::ADVERB, WordType::PREPOSITION, WordType::CONJUNCTION, WordType::END},

     // WordType::ADJECTIVE
     {WordType::NOUN, WordType::ADJECTIVE, WordType::WT_COUNT, WordType::WT_COUNT, WordType::WT_COUNT},

     // WordType::ADVERB
     {WordType::VERB, WordType::ADJECTIVE, WordType::ADVERB, WordType::WT_COUNT, WordType::WT_COUNT},

     // WordType::PRONOUN
     {WordType::VERB, WordType::ADVERB, WordType::WT_COUNT, WordType::WT_COUNT, WordType::WT_COUNT},

     // WordType::PREPOSITION
     {WordType::DETERMINER, WordType::NOUN, WordType::PRONOUN, WordType::WT_COUNT, WordType::WT_COUNT},

     // WordType::CONJUNCTION
     {WordType::NOUN, WordType::PRONOUN, WordType::VERB, WordType::WT_COUNT, WordType::WT_COUNT},

     // WordType::DETERMINER
     {WordType::ADJECTIVE, WordType::NOUN, WordType::WT_COUNT, WordType::WT_COUNT, WordType::WT_COUNT},

     // WordType::INTERJECTION
     {WordType::PRONOUN, WordType::NOUN, WordType::VERB, WordType::WT_COUNT, WordType::WT_COUNT},

     // WordType::END
     {WordType::WT_COUNT, WordType::WT_COUNT, WordType::WT_COUNT, WordType::WT_COUNT, WordType::WT_COUNT}}};

#include <gtest/gtest.h>

#include <string>
#include <vector>

extern "C" {
#include "word_generator.h"
}

namespace {

struct WordCollector {
    std::vector<std::string> words;
    size_t stop_after = 0;
};

bool collect_word(const char *word, void *user_data) {
    auto *collector = static_cast<WordCollector *>(user_data);
    collector->words.emplace_back(word);
    if (collector->stop_after > 0 && collector->words.size() >= collector->stop_after) {
        return false;
    }
    return true;
}

}  // namespace

TEST(GenerateWords, ProducesAllBinaryStringsOfLengthThree) {
    WordCollector collector;
    ASSERT_EQ(generate_words("01", 2, 3, collect_word, &collector), GENERATE_OK);
    EXPECT_EQ(collector.words.size(), 8u);
    EXPECT_EQ(collector.words.front(), "000");
    EXPECT_EQ(collector.words.back(), "111");
}

TEST(GenerateWords, EmitsLexicographicOrder) {
    WordCollector collector;
    ASSERT_EQ(generate_words("ab", 2, 2, collect_word, &collector), GENERATE_OK);
    const std::vector<std::string> expected = {"aa", "ab", "ba", "bb"};
    EXPECT_EQ(collector.words, expected);
}

TEST(GenerateWords, CountMatchesAlphabetSizeRaisedToWordLength) {
    WordCollector collector;
    ASSERT_EQ(generate_words("abcde", 5, 4, collect_word, &collector), GENERATE_OK);
    EXPECT_EQ(collector.words.size(), 625u);
}

TEST(GenerateWords, CallbackCanStopEnumeration) {
    WordCollector collector;
    collector.stop_after = 3;
    ASSERT_EQ(generate_words("abc", 3, 5, collect_word, &collector), GENERATE_OK);
    EXPECT_EQ(collector.words.size(), 3u);
}

TEST(GenerateWords, SingleCharacterAlphabetProducesOneWord) {
    WordCollector collector;
    ASSERT_EQ(generate_words("x", 1, 4, collect_word, &collector), GENERATE_OK);
    ASSERT_EQ(collector.words.size(), 1u);
    EXPECT_EQ(collector.words.front(), "xxxx");
}

TEST(GenerateWords, AlphabetWithDuplicatesProducesDuplicateOutputs) {
    WordCollector collector;
    ASSERT_EQ(generate_words("aa", 2, 2, collect_word, &collector), GENERATE_OK);
    EXPECT_EQ(collector.words.size(), 4u);
    for (const auto &word : collector.words) {
        EXPECT_EQ(word, "aa");
    }
}

TEST(GenerateWords, AcceptsAlphabetWithoutNulTerminator) {
    const char raw_alphabet[3] = {'x', 'y', 'z'};
    WordCollector collector;
    ASSERT_EQ(generate_words(raw_alphabet, 3, 2, collect_word, &collector), GENERATE_OK);
    EXPECT_EQ(collector.words.size(), 9u);
    EXPECT_EQ(collector.words.front(), "xx");
    EXPECT_EQ(collector.words.back(), "zz");
}

TEST(GenerateWords, RejectsNullAlphabet) {
    EXPECT_EQ(generate_words(nullptr, 3, 2, collect_word, nullptr),
              GENERATE_INVALID_ARGUMENT);
}

TEST(GenerateWords, RejectsZeroAlphabetSize) {
    EXPECT_EQ(generate_words("abc", 0, 2, collect_word, nullptr),
              GENERATE_INVALID_ARGUMENT);
}

TEST(GenerateWords, RejectsZeroWordLength) {
    EXPECT_EQ(generate_words("abc", 3, 0, collect_word, nullptr),
              GENERATE_INVALID_ARGUMENT);
}

TEST(GenerateWords, RejectsNullCallback) {
    EXPECT_EQ(generate_words("abc", 3, 2, nullptr, nullptr),
              GENERATE_INVALID_ARGUMENT);
}

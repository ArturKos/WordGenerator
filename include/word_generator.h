#ifndef WORD_GENERATOR_H
#define WORD_GENERATOR_H

#include <stddef.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Callback invoked once per generated word.
 *
 * The buffer pointed to by @p word is reused on every call, so callbacks
 * that need to retain the value must copy it.
 *
 * @param word      NUL-terminated word of length equal to @c word_length.
 * @param user_data Opaque pointer forwarded from generate_words().
 * @return @c true to continue generation, @c false to stop early.
 */
typedef bool (*word_callback_fn)(const char *word, void *user_data);

/**
 * @brief Result codes returned by generate_words().
 */
typedef enum {
    GENERATE_OK = 0,                /**< All words produced (or callback stopped cleanly). */
    GENERATE_INVALID_ARGUMENT = -1, /**< NULL pointer or zero size/length. */
    GENERATE_OUT_OF_MEMORY = -2     /**< Internal allocation failed. */
} generate_status_t;

/**
 * @brief Enumerate every word of a fixed length over an alphabet.
 *
 * Produces @c alphabet_size raised to @c word_length distinct index
 * combinations in lexicographic order with respect to the alphabet's
 * character order. The callback fires once per word.
 *
 * The alphabet does not need to be NUL-terminated; only @c alphabet_size
 * bytes are read. Duplicate characters in the alphabet are allowed and
 * produce duplicate output words.
 *
 * @param alphabet      Source characters. Must not be NULL.
 * @param alphabet_size Number of characters in @p alphabet. Must be > 0.
 * @param word_length   Length of each generated word. Must be > 0.
 * @param callback      Invoked once per word. Must not be NULL.
 * @param user_data     Opaque pointer forwarded to @p callback.
 * @return ::GENERATE_OK on success or clean callback abort,
 *         ::GENERATE_INVALID_ARGUMENT on bad arguments,
 *         ::GENERATE_OUT_OF_MEMORY on allocation failure.
 */
generate_status_t generate_words(const char *alphabet,
                                 size_t alphabet_size,
                                 size_t word_length,
                                 word_callback_fn callback,
                                 void *user_data);

#ifdef __cplusplus
}
#endif

#endif

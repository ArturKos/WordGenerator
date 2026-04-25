#include "word_generator.h"

#include <stdlib.h>

static bool advance_indices(size_t *indices, size_t length, size_t alphabet_size) {
    for (size_t i = length; i > 0; --i) {
        size_t position = i - 1;
        if (indices[position] + 1 < alphabet_size) {
            indices[position]++;
            return true;
        }
        indices[position] = 0;
    }
    return false;
}

static void render_word(const char *alphabet,
                        const size_t *indices,
                        size_t word_length,
                        char *out_buffer) {
    for (size_t i = 0; i < word_length; ++i) {
        out_buffer[i] = alphabet[indices[i]];
    }
    out_buffer[word_length] = '\0';
}

generate_status_t generate_words(const char *alphabet,
                                 size_t alphabet_size,
                                 size_t word_length,
                                 word_callback_fn callback,
                                 void *user_data) {
    if (alphabet == NULL || callback == NULL ||
        alphabet_size == 0 || word_length == 0) {
        return GENERATE_INVALID_ARGUMENT;
    }

    size_t *indices = calloc(word_length, sizeof(*indices));
    if (indices == NULL) {
        return GENERATE_OUT_OF_MEMORY;
    }

    char *buffer = malloc(word_length + 1);
    if (buffer == NULL) {
        free(indices);
        return GENERATE_OUT_OF_MEMORY;
    }

    do {
        render_word(alphabet, indices, word_length, buffer);
        if (!callback(buffer, user_data)) {
            break;
        }
    } while (advance_indices(indices, word_length, alphabet_size));

    free(buffer);
    free(indices);
    return GENERATE_OK;
}

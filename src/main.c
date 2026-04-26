#include "word_generator.h"

#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static bool print_word_to_stdout(const char *word, void *user_data) {
    (void)user_data;
    return puts(word) >= 0;
}

static bool parse_word_length(const char *text, size_t *out_length) {
    char *end;
    errno = 0;
    long parsed = strtol(text, &end, 10);
    if (errno != 0 || *end != '\0' || parsed <= 0 || parsed > INT_MAX) {
        return false;
    }
    *out_length = (size_t)parsed;
    return true;
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr,
                "Usage: %s <alphabet> <length>\n"
                "Generate every word of <length> characters over <alphabet>.\n",
                argc > 0 ? argv[0] : "word_generator");
        return EXIT_FAILURE;
    }

    const char *alphabet = argv[1];
    size_t alphabet_size = strlen(alphabet);
    if (alphabet_size == 0) {
        fprintf(stderr, "Error: <alphabet> must not be empty.\n");
        return EXIT_FAILURE;
    }

    size_t word_length;
    if (!parse_word_length(argv[2], &word_length)) {
        fprintf(stderr, "Error: <length> must be a positive integer.\n");
        return EXIT_FAILURE;
    }

    generate_status_t status = generate_words(
        alphabet, alphabet_size, word_length, print_word_to_stdout, NULL);

    switch (status) {
        case GENERATE_OK:
            return EXIT_SUCCESS;
        case GENERATE_INVALID_ARGUMENT:
            fprintf(stderr, "Error: invalid arguments.\n");
            return EXIT_FAILURE;
        case GENERATE_OUT_OF_MEMORY:
            fprintf(stderr, "Error: out of memory.\n");
            return EXIT_FAILURE;
    }
    return EXIT_FAILURE;
}

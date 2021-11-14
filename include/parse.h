#ifndef PARSE_H_
#define PARSE_H_

#include <stddef.h>

/*
 * Fills string array 'tokens' with pointers 
 * to the first non-delim characters if 'buf'.
 *
 * At most 'n_tokens' characters are written.
 * Returns the amount of tokens were read. You
 * can use that amount to realloc() your 'tokens' array.
 */
size_t extract_tokens(char *const buf, char **tokens, 
                      const char *const delim, size_t n_tokens);

/*
 * Counts occurrences of character in a string.
 */
size_t occurs(const char *const str, const char ch);

/*
 * Removes spaces at the beginning and at the end of the 
 * line (string terminated with '\n') by placing '\0' symbol.
 * Additionally sets 'end' pointer -- the symbol after last '\0'.
 *
 * Returns a new string beginning. 
 */
char *strip_spaces(char *str, char **end = nullptr);


#endif /* PARSE_H_ */

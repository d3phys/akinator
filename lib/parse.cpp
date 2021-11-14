#include <assert.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include <parse.h>

char *strip_spaces(char *str, char **end)
{
        char *ch = str;
        while (isspace(*ch)) {
                if (*ch == '\0') {
                        *end = ch;
                        return ch;
                }

                ch++;
        }

        str = ch;

        char *whspace = ch;
        while (*ch != '\n') {
                if (*ch == '\0') {
                        *end = ch;
                        break;
                }

                if (!isspace(*ch))
                        whspace = ch + 1;

                ch++;
        }

        if (*ch != '\0' && end)
                *end = ch + 1;

        *whspace = '\0';

        return str;
}

size_t extract_tokens(char *const buf, char **tokens, 
                      const char *const delim, size_t n_tokens) 
{
        assert(buf);
        assert(delim);
        assert(tokens);

        size_t n_toks = 0;

        char *tok = strtok(buf, delim);
        while (tok && n_tokens-- > 0) {
                *tokens++ = tok;
                n_toks++;
                tok = strtok(nullptr, delim);
        }

        return n_toks;
}

size_t occurs(const char *const str, const char ch) 
{
        assert(str);

        const char *pos = str;
        size_t n_ch = 0;
        while (*pos != '\0')
                if (*pos++ == ch)
                        n_ch++;
        return n_ch;
}



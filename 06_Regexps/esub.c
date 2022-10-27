#include <stdio.h>
#include <stdlib.h>
#include <regex.h>
#include <string.h>

#define MATCH_ARRAY_SIZE 1

void esub(char *regexp, char *substitution, char *string) {
    regex_t regex_compiled;

    int res = regcomp(&regex_compiled, regexp, REG_EXTENDED);

    if (res) {
        size_t error_message_len = regerror(res, &regex_compiled, NULL, 0);
        char *error_buf = calloc(error_message_len, sizeof(*error_buf));
        regerror(res, &regex_compiled, error_buf, error_message_len);
        fprintf(stderr, "%s\n", error_buf);
        free(error_buf);
        regfree(&regex_compiled);
        exit(1);
    }

    regmatch_t pmatch[MATCH_ARRAY_SIZE];
    res = regexec(&regex_compiled, string, MATCH_ARRAY_SIZE, pmatch, 0);

    char *cur_str = string;
    while (*cur_str != '\0') {
        if (res == REG_NOMATCH) {
            printf("%s", cur_str);
            break;
        } else if (res != 0) {
            size_t error_message_len = regerror(res, &regex_compiled, NULL, 0);
            char *error_buf = calloc(error_message_len, sizeof(*error_buf));
            regerror(res, &regex_compiled, error_buf, error_message_len);
            fprintf(stderr, "%s\n", error_buf);
            free(error_buf);
            regfree(&regex_compiled);
            exit(1);
        }

        char tmp = cur_str[pmatch[0].rm_so];
        cur_str[pmatch[0].rm_so] = '\0';
        printf("%s%s", cur_str, substitution);
        cur_str[pmatch[0].rm_so] = tmp;

        cur_str += pmatch[0].rm_eo;
        res = regexec(&regex_compiled, cur_str, MATCH_ARRAY_SIZE, pmatch, 0);
    }

    putchar('\n');
    regfree(&regex_compiled);
}


// driver
int main(int argc, char *argv[]) {
    if (argc != 4) {
        fprintf(stderr, "Wrong number of cmd arguments:\n"
                        "\texpected: 3 . got: %d\n"
                        "This three arguments are:\n"
                        "\t1) regexp\n"
                        "\t2) substitution\n"
                        "\t3) string\n",
                argc);
        return 1;
    }

    char *regexp = argv[1];
    char *substitution = argv[2];
    char *string = argv[3];

    esub(regexp, substitution, string);
}

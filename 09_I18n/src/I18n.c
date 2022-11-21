#include <stdio.h>
#include <locale.h>
#include <libintl.h>
#include <stdlib.h>
#include <string.h>

#define _(STRING) gettext(STRING)
const char *YES = "yes";


int get_yes_or_no() {
    char *str = NULL;
    size_t str_size = 0;

    if (getline(&str, &str_size, stdin) < 0) {
        fprintf(stderr, _("Error: expected string\n"));
        exit(1);
    }

    int n = strlen(str);
    if (n > 0 && str[n - 1] == '\n') str[n - 1] = '\0';

    return strcmp(str, _(YES)) == 0;
}

void guess_number_game() {
    printf(_("Pick a natural number in range [1, 100]\n"));

    int high = 100;
    int low = 1;
    int mid;

    while (low != high) {
        mid = (low + high) >> 1;
        printf(_("Is your number more than %d?\nInput yes if it is or any other string otherwise\n"), mid);
        int guess_is_greater = get_yes_or_no();

        if (guess_is_greater) {
            low = mid + 1;
        } else {
            high = mid;
        }
    }

    printf(_("Your number is %d! If not then you picked natural number not in range [1, 100].\n"), low);
    printf(_("Bye!\n"));
}

int main() {
    setlocale(LC_ALL, "");
    bindtextdomain("I18n", "translations");
    textdomain("I18n");

    guess_number_game();

    return 0;
}

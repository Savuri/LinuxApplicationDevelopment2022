#include <stdio.h>
#include <locale.h>
#include <libintl.h>
#include <stdlib.h>
#include <string.h>

#define _(STRING) gettext(STRING)
#define VERSION "1.0.0"
#define MIN(X, Y) (((X) < (Y)) ? (X) : (Y))

static const char *YES = "yes";
static int arg_roman = 0;
static int arg_help = 0;
static int arg_version = 0;

/** Convert \p i into roman if arg_roman was set.
 *
 * @param i integer to convert
 * @param dest result to write \p i representation in roman or usual number representation if arg_roman was not set
 * @return pointer on \p dest
 */
static char *convert(int i, char dest[9]) {
    static const char *to_roman[] = {
            "N",
            "I",
            "II",
            "III",
            "IV",
            "V",
            "VI",
            "VII",
            "VIII",
            "IX",
            "X",
            "XI",
            "XII",
            "XIII",
            "XIV",
            "XV",
            "XVI",
            "XVII",
            "XVIII",
            "XIX",
            "XX",
            "XXI",
            "XXII",
            "XXIII",
            "XXIV",
            "XXV",
            "XXVI",
            "XXVII",
            "XXVIII",
            "XXIX",
            "XXX",
            "XXXI",
            "XXXII",
            "XXXIII",
            "XXXIV",
            "XXXV",
            "XXXVI",
            "XXXVII",
            "XXXVIII",
            "XXXIX",
            "XL",
            "XLI",
            "XLII",
            "XLIII",
            "XLIV",
            "XLV",
            "XLVI",
            "XLVII",
            "XLVIII",
            "XLIX",
            "L",
            "LI",
            "LII",
            "LIII",
            "LIV",
            "LV",
            "LVI",
            "LVII",
            "LVIII",
            "LIX",
            "LX",
            "LXI",
            "LXII",
            "LXIII",
            "LXIV",
            "LXV",
            "LXVI",
            "LXVII",
            "LXVIII",
            "LXIX",
            "LXX",
            "LXXI",
            "LXXII",
            "LXXIII",
            "LXXIV",
            "LXXV",
            "LXXVI",
            "LXXVII",
            "LXXVIII",
            "LXXIX",
            "LXXX",
            "LXXXI",
            "LXXXII",
            "LXXXIII",
            "LXXXIV",
            "LXXXV",
            "LXXXVI",
            "LXXXVII",
            "LXXXVIII",
            "LXXXIX",
            "XC",
            "XCI",
            "XCII",
            "XCIII",
            "XCIV",
            "XCV",
            "XCVI",
            "XCVII",
            "XCVIII",
            "XCIX",
            "C",
    };

    if (arg_roman) {
        sprintf(dest, "%s", to_roman[i]);
    } else {
        sprintf(dest, "%d", i);
    }

    return dest;
}

/** Prints help message
 */
static void help(void) {
    printf(_("I18n [-r] [--help]\n"
             "\n"
             "This program guesses the number 1...100 using the half division method\n"
             "\n"
             "First of all, it asks you to pick a number from 1 to 100.\n"
             "Then it asks \"Is your number more than 50?\"\n"
             "Based on the answer, selects a half-interval and repeats it in a cycle\n"
             "When it guesses, it answers\n"
             "\n"
             "Options:\n"
             "\t--help - print help\n"
             "\t-r - work with roman numbers\n"));
}

/** Read yes from stdin in international (ru/en) format and return true if it was yes
 * @return nonzero if user input yes. Zero otherwise
 */
static int get_yes_or_no(void) {
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
/** Start guess game.
 *
 * Returns nothing
 */
static void guess_number_game() {
    int low = 1;
    int high = 100;
    int mid;

    char buf1[9];
    char buf2[9];
    char buf3[9];

    printf(_("Pick a natural number in range [%s, %s]\n"), convert(low, buf1), convert(high, buf2));

    while (low != high) {
        mid = (low + high) >> 1;
        printf(_("Is your number more than %s?\nInput yes if it is or any other string otherwise\n"),
               convert(mid, buf1));
        int guess_is_greater = get_yes_or_no();

        if (guess_is_greater) {
            low = mid + 1;
        } else {
            high = mid;
        }
    }

    printf(_("Your number is %s! If not then you picked natural number not in range [%s, %s].\n"), convert(low, buf1),
           convert(1, buf2), convert(100, buf3));
    printf(_("Bye!\n"));
}

/** @mainpage guess game
 *  Guess game
 *  @section SYNOPSIS
 *  I18n [\a --help] [\a -r]
 *  @section DESCRIPTION
 * This program guesses the number 1...100 using the half division method
 * First of all, it asks you to pick a number from 1 to 100.
 * Then it asks "Is your number more than 50?"
 * Based on the answer, selects a half-interval and repeats it in a cycle
 * When it guesses, it answers
 *
 * @section OPTIONS
 * - *help* - print help
 * - *r* - work with roman numbers
 */
int main(int argc, const char *argv[]) {
    setlocale(LC_ALL, "");
    bindtextdomain("I18n", "translations");
    textdomain("I18n");

    for (int i = 1; i < argc; ++i) {
        if (!strncmp(argv[i], "-r", MIN(strlen(argv[i]), sizeof("-r")))) {
            arg_roman = 1;
        } else if (!strncmp(argv[i], "--help", MIN(strlen(argv[i]), sizeof("--help")))) {
            arg_help = 1;
        } else if (!strncmp(argv[i], "--version", sizeof(argv[i], "--version"))){
            arg_version = 1;
        } else {
            printf(_("Unexpected command line argument %s\n"), argv[i]);
            exit(1);
        }
    }

    if (arg_help) {
        help();
    } else if (arg_version) {
        printf("%s", VERSION);
    } else {
        guess_number_game();
    }

    return 0;
}

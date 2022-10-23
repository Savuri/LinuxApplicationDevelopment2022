#include <stdio.h>
#include <stdlib.h>

void help(void) {
    printf("Welcome to range program. This program prints range of number configured in cmd arguments\n"
           "Usage:\n"
           "\trange N\n"
           "\trange M N\n"
           "\trange M N S\n"
           "Where:\n"
           "\tM - integer beginning of range\n"
           "\tN - integer end of the range\n"
           "\tS - step\n"
           "\n"
           "All other usages are inappropriate.\n");
}

/*
 * return value zero means ok
 */
int read_int(char *from, long *res) {
    char *end;
    *res = strtol(from, &end, 10);
    return *end != '\0';
}

void print_range(long start, long end, long step) {
    long cur = start;

    while (cur < end) {
        printf("%ld\n", cur);
        cur += step;
    }
}

// driver
int main (int argc, char * argv[]) {
    long n;
    long m = 0;
    long s = 1;

    if (argc == 1 || argc > 4) {
        help();

        if (argc > 4) {
            printf("Too many arguments\n");
        }

        return 0;
    }

    if (argc == 2) {
        if (read_int(argv[1], &n)) {
            fprintf(stderr, "Wrong N\n");
            return 1;
        }
    } else if (argc >= 3) {
        if (read_int(argv[1], &m)) {
            fprintf(stderr, "Wrong M\n");
            return 1;
        }

        if (read_int(argv[2], &n)) {
            fprintf(stderr, "Wrong N\n");
            return 1;
        }
    }

    if (argc == 4) {
        if (read_int(argv[3], &s) || s < 0) {
            fprintf(stderr, "Wrong S\n");
            return 1;
        }
    }

    print_range(m, n, s);
}

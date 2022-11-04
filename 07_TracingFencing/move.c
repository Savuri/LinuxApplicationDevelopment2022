#include <stdio.h>
#include <stdlib.h>
#include <regex.h>
#include <string.h>
#include <errno.h>
#include <assert.h>

#define BUF_SIZE 1024

void move(const char *input_file_name, const char *output_file_name) {
    FILE *in = fopen(input_file_name, "r");

    if (in == NULL) {
        fprintf(stderr, "Can not open input file: %s\n", strerror(errno));
        exit(1);
    }

    FILE *out = fopen(output_file_name, "w+");

    if (out == NULL) {
        fprintf(stderr, "Can not open output file: %s\n", strerror(errno));
        assert(fclose(in) == 0);
        exit(1);
    }

    char *buf = calloc(BUF_SIZE, sizeof(*buf));

    if (buf == NULL) {
        fprintf(stderr, "Can not allocate memory for buffer: %s\n", strerror(errno));
        assert(fclose(in) == 0);
        assert(fclose(out) == 0);
        free(buf);
        exit(1);
    }

    size_t n;

    while ((n = fread(buf, sizeof(*buf), BUF_SIZE, in)) != 0) {
        if (fwrite(buf, sizeof(*buf), n, out) == 0) {
            fprintf(stderr, "fwrite error: %s\n", strerror(errno));
            assert(fclose(in) == 0);
            assert(fclose(out) == 0);
            free(buf);
            exit(1);
        }
    }

    if (ferror(in)) {
        fprintf(stderr, "Error on reading: %s\n", strerror(errno));
        assert(fclose(in) == 0);
        assert(fclose(out) == 0);
        free(buf);
        exit(1);
    }

    assert(fclose(in) == 0);
    assert(fclose(out) == 0);
    free(buf);

    if (remove(input_file_name) < 0) {
        fprintf(stderr, "Was not able to remove input file: %s\n", strerror(errno));
        exit(1);
    }
}


// driver
int main(int argc, char *argv[]) {
    if (argc != 3) {
        errno = EINVAL;
        fprintf(stderr, "Expected 2 cmd arguments\n");
        return 1;
    }

    move(argv[1], argv[2]);
}

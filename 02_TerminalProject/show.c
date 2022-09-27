#include <ncurses.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <locale.h>

#define DX 3
#define BEGIN_LINES_CNT 4

enum KEYS {
    KEY_ESC = 0x1B,
    KEY_SPACE = ' '
};

char **read_file(char *file, size_t *ret_lines_count) {
    FILE *f = fopen(file, "r");
    if (!f) {
        fprintf(stderr, "Can't open file: [%s], [%s]\n", file, strerror(errno));
        exit(1);
    }

    size_t lines_count = BEGIN_LINES_CNT;
    char **content = (char **) malloc(sizeof(*content) * lines_count);

    char *buf = NULL;
    size_t buf_size = 0;

    size_t cur_lines_count = 0;

    while (getline(&buf, &buf_size, f) != -1) {
        if (cur_lines_count == lines_count) {
            lines_count *= 2;
            content = (char **) realloc(content, sizeof(*content) * lines_count);
        }

        content[cur_lines_count] = buf;

        buf = NULL;
        buf_size = 0;

        ++cur_lines_count;
    }

    if (errno) {
        fprintf(stderr, "getline error: %s\n", strerror(errno));
        exit(1);
    }

    *ret_lines_count = cur_lines_count;
    content = (char **) realloc(content, sizeof(*content) * cur_lines_count);

    if (fclose(f) != 0) {
        fprintf(stderr, "fclose error %s\n", strerror(errno));
        exit(1);
    }

    return content;
}


size_t min(size_t l, size_t r) {
    return (l < r) ? l : r;
}

void draw_content(WINDOW *win, size_t height, char **content, size_t lines_count, size_t top, size_t left) {
    werase(win);

    for (size_t i = 0; i + top < min(height + top, lines_count); ++i) {
        mvwprintw(win, i + 1, 1, "%4lu: %s\n", top + i + 1, (left < strlen(content[top + i])) ? (content[top + i] + left) : "");
    }
    box(win, 0, 0);
    wrefresh(win);
}

void free_matrix(char **arr, size_t n) {
    for (size_t i = 0; i < n; ++i) {
        free(arr[i]);
    }

    free(arr);
}


int main(int argc, char **argv) {
    if (argc != 2) {
        printf("Usage: ./show file_name_to_open");
        exit(0);
    }

    size_t lines_count;
    char **content = read_file(argv[1], &lines_count);

    initscr();
    noecho();
    cbreak();

    size_t height = LINES - 2 * DX;
    size_t width = COLS - 2 * DX;
    WINDOW *win = newwin(height, width, DX, DX);

    if (win == NULL) {
        fprintf(stderr, "Can't create window\n");
        exit(1);
    }

    mvprintw(0, 0, "File: %s", argv[1]);
    refresh();
    keypad(win, TRUE);

    size_t top = 0;
    size_t left = 0;
    int done = 0;
    do {
        draw_content(win, height, content, lines_count, top, left);

        switch (wgetch(win)) {
            case KEY_ESC:
                done = 1;
                break;
            case KEY_SPACE:
            case KEY_DOWN:
                top = (top + height - 2 < lines_count) ? (top + 1) : top;
                break;
            case KEY_UP:
                top = (top == 0) ? top : (top - 1);
                break;
            case KEY_LEFT:
                left = (left == 0) ? (0) : (left - 1);
                break;
            case KEY_RIGHT:
                left += 1;
                break;
        }
    } while (!done);


    free_matrix(content, lines_count);
    delwin(win);
    endwin();
}
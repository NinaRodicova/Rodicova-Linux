#include <curses.h>
#include <locale.h>
#define DX 7
#define DY 3

/**
 * This function prints string from file f which
 * starting from x_start position into win to position y.
 * -1 - returns if by writing EOF was readen.
 * 0 - returns if EOF was not readen.
 */
int
print_str(WINDOW *win, FILE *f, int x_start, int y)
{
    int c;
    int pos = 0;
    char buf[COLS - 2 * DX - 1];
    int i = 0;
    int x_end = x_start + COLS - 2 * DX - 2;

    while (((c = fgetc(f)) != EOF) && (pos < x_end)) {
        if (pos >= x_start) {
            buf[i] = c;
            i++;
        }
        /* The win is bigger then string. */
        if (c == '\n') {
            if (pos < x_start) {
                buf[0] = '\n';
                i++;
            }
            buf[i] = '\0';
            mvwaddstr(win, y, 0, buf);
            return 0;
        }
        pos++;
    }

    while ((c != EOF) && (c != '\n'))
        c = fgetc(f);

    /* EOF was not readen */
    if (c == EOF) {
        buf[i] = '\n';
        buf[i + 1] = '\0';
        mvwaddstr(win, y, 0, buf);
        return -1;
    }

    /* The string is bigger then win. */
    buf[COLS - 2 * DX - 3] = '\n';
    buf[COLS - 2 * DX - 2] = '\0';
    mvwaddstr(win, y, 0, buf);
    return 0;
}

/**
 * This function writes strings from file `file_name`.
 * y_start, x_start are start positions in the file.
 * -1 - returns if by writing EOF was readen.
 * 0 - returns if EOF was not readen.
 */
int
print_win(WINDOW *win, const char *file_name, int y_start, int x_start)
{
    FILE *f = fopen(file_name, "r");
    int c;
    /* Skip some strings */
    for (int i = 0; i < y_start; i++) {
        while ((c = fgetc(f)) != EOF && c != '\n') {
        }
        if (c == EOF) {
            fclose(f);
            return -1;
        }
    }
    int y = 0;
    int y_end = y_start + LINES - 2 * DY - 2;

    /* Print necessary strings */
    for (int i = y_start; i < y_end; i++) {
        if (print_str(win, f, x_start, y) == -1) {
            fclose(f);
            return -1;
        }
        y++;
    }
    fclose(f);
    return 0;
}

int main(int argc, char *argv[]) {
    WINDOW *frame, *win;
    setlocale(LC_ALL, "");
    initscr();
    noecho();
    cbreak();
    printw("File: ");
    printw("%s", argv[1]);
    refresh();
    frame = newwin(LINES - 2 * DY, COLS - 2 * DX, DY, DX);
    box(frame, 0, 0);
    mvwaddstr(frame, 0, (int)((COLS - 2 * DX - 5) / 2), argv[1]);
    wrefresh(frame);
    win = newwin(LINES - 2 * DY - 2, COLS - 2 * DX - 2, DY + 1, DX + 1);
    keypad(win, TRUE);
    int x_start = 0;
    int y_start = 0;
    int c = 0;
    int code = 0;
    print_win(win, argv[1], y_start, x_start);
    while ((c = wgetch(win)) != 27) {
        werase(win);
        if (c == 258 || c == 32) { /* Down arrow or space */
            if (code == 0)
                y_start += 1;
        } else if (c == 259) { /* Up arrow */
            if (y_start != 0)
                y_start -= 1;
        } else if (c == 260) { /* Left arrow */
            if (x_start != 0)
                x_start -= 1;
        } else if (c == 261) { /* Right arrow */
            x_start += 1;
        } else if (c == 338) { /* Page down */
            if (code == 0)
                y_start += LINES - 2 * DY - 1;
        } else if (c == 339) { /* Page up */
            y_start -= LINES - 2 * DY - 1;
            if (y_start < 0)
                y_start = 0;
        }
        code = print_win(win, argv[1], y_start, x_start);
        wrefresh(frame);
    }
    delwin(win);
    delwin(frame);
    endwin();
    return 0;
}

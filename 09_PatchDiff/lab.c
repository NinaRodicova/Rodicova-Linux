#include <time.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char**argv) {
    int N = 6;
    char stone = '#';
    char room = '.';
    srand(time(NULL));

    int N_stone = (2 * N - 1) * 4 + N * (N - 1) * 2;
    int min_N_stone = N_stone * 0.15 + 1;

    char **labirint = malloc(sizeof(char *) * (2 * N + 1));
    for (int i = 0; i < 2 * N + 1; i++) {
        labirint[i] = malloc(sizeof(char) * (2 * N + 1));
    }
    for (int i = 0; i < 2 * N + 1; i ++) {
        for (int j = 0; j < 2 * N + 1; j++)
            labirint[i][j] = stone;
    }

    int base = rand() % 2;
    int i = 1;
    for (int ii = 0; ii < N; ii++) {
        for (int j = 1; j < 2 * N; j++) {
            if (base == 1)
                labirint[i][j] = room;
            else
                labirint[j][i] = room;
            N_stone --;
        }
        i++;
        i++;
    }
    i = 2;
    for (int ii = 0; ii < N - 1; ii++) {
        int j = (rand() % N) * 2 + 1;
        if (base == 1)
            labirint[i][j] = room;
        else
            labirint[j][i] = room;
        N_stone --;
        i++;
        i++;
    }

    for (int k = 0; k < 2 * (N_stone - min_N_stone); k ++) {
        int i = rand() % (2 * N - 1) + 1;
        int j;
        if (i % 2 == 1)
            j = (rand() % (N - 1)) * 2 + 2;
        else
            j = (rand() % N) * 2 + 1;
        if (labirint[i][j] != room) {
            labirint[i][j] = room;
            N_stone --;
        }
        if (N_stone == min_N_stone)
            break;
    }

    for (int i = 0; i < 2 * N + 1; i++) {
        for (int j = 0; j < 2 * N + 1; j++)
            printf("%c", labirint[i][j]);
        printf("\n");
    }

    for (int i = 0; i < 2 * N + 1; i++) {
        free(labirint[i]);
    }
    free(labirint);
    return 0;
}


#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    int i = 0;
    int N = 0;
    int M = 0;
    int S = 0;
    if (argc == 1) {
        printf("help\n");
    } else if (argc == 2) {
        N = atoi(argv[1]);
        for (i = 0; i < N; i++)
            printf("%d\n", i);
    } else {
        M = atoi(argv[1]);
        N = atoi(argv[2]);
        if (argc == 4)
            S = atoi(argv[3]);
        else
            S = 1;
        for (i = M; i < N; i = i + S)
            printf("%d\n", i);
    }
    return 0;
}
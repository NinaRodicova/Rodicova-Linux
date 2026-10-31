#include <stdio.h>
#include <errno.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: move infile outfile\n");
        return 1;
    }

    const char *infile = argv[1];
    const char *outfile = argv[2];

    FILE *in_f = fopen(infile, "r");
    if (in_f == 0) {
        int err = errno;
        perror("Can not open infile");
        return err;
    }

    if (fseek(in_f, 0, SEEK_END) != 0) {
        int err = errno;
        perror("Error in fseek");
        fclose(in_f);
        return err;
    } 
    long size = ftell(in_f);
    if (size < 0) {
        int err = errno;
        perror("Error in ftell");
        fclose(in_f);
        return err;
    }
    rewind(in_f);

    char *buf = NULL;
    if (size > 0) {
        buf = malloc(size);

        size_t n = fread(buf, 1, size, in_f);
        if (n < size) {
            int err = errno;
            perror("Can not read infile");
            free(buf);
            fclose(in_f);
            return err;
        }
    }

    FILE *out_f = fopen(outfile, "w");
    if (out_f < 0) {
        int err = errno;
        perror("Can not open outfile");
        if (size > 0)
            free(buf);
        fclose(in_f);
        return err;
    }

    if (size > 0) {
        size_t n = fwrite(buf, 1, size, out_f);
        if (n != size || ferror(out_f)) {
            free(buf);
            fclose(in_f);
            fclose(out_f);
            return 13;
        }

        free(buf);
    }

    if (fclose(in_f) != 0) {
        int err = errno;
        perror("Can not close infile");
        fclose(out_f);
        return err;
    }

    if (fclose(out_f) != 0) {
        int err = errno;
        perror("Can not close outfile");
        return err;
    }

    if (remove(infile) != 0) {
        int err = errno;
        perror("Can not remove infile");
        return err;
    }

    return 0;
}

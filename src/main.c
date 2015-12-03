/* -*- Mode: c; tab-width: 4; c-basic-offset: 4; indent-tabs-mode: nil; -*- */
#define __STDC_WANT_LIB_EXT1__ 1

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "entropy.h"

#define BUFSIZE 1024


int entropy(FILE *fp, double *out_e)
{
    struct entropy_ctx *ctx;

    ctx = malloc(entropy_sizeof());
    entropy_init(ctx);

    uint8_t buf[BUFSIZE];
    size_t len;
    do {
        len = fread(buf, sizeof(buf[0]), BUFSIZE, fp);
        entropy_update(ctx, buf, len);
    } while (len == BUFSIZE);

    *out_e = entropy_current(ctx);
    
    free(ctx);
    return 0;
}

int main(int argc, char *argv[])
{
    if (argc < 2) {
        printf("no args\n");
        return EXIT_SUCCESS;
    }

    for (int i = 1; i < argc; i++) {
        double e;
        const char *path = argv[i];
        FILE *fp;
        if (strlen(path) == 1 && path[0] == '-') {
            fp = stdin;
        } else {
            fp = fopen(path, "rb");
        }
        if (!fp) {
            printf("fopen failed: %s\n", path);
            continue;
        }
        if (entropy(fp, &e) == 0) {
            printf("%s: %f\n", path, e);
        }
        if (fp != stdin) {
            fclose(fp);
        }
    }
    return EXIT_SUCCESS;
}

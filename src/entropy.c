/* -*- Mode: c; tab-width: 4; c-basic-offset: 4; indent-tabs-mode: nil; -*- */
#define __STDC_WANT_LIB_EXT1__ 1

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <math.h>

#include "entropy.h"


struct entropy_ctx {
    uint64_t table[256];
    size_t total;
};


size_t entropy_sizeof(void)
{
    return sizeof(struct entropy_ctx);
}

void entropy_init(struct entropy_ctx *ctx)
{
    memset(ctx->table, 0, sizeof(ctx->table));
    ctx->total = 0;
}

void entropy_update(struct entropy_ctx *ctx, uint8_t *buf, size_t len)
{
    for (size_t i = 0; i < len; i++) {
        ctx->table[buf[i]] += 1;
    }
    ctx->total += len;
}

double entropy_current(const struct entropy_ctx *ctx)
{
    double e = 0.0;
    if (ctx->total == 0) {
        return e;
    }
    const double total = ctx->total;
    const size_t size = sizeof(ctx->table) / sizeof(ctx->table[0]);
    for (size_t i = 0; i < size; i++) {
        if (ctx->table[i]) {
            const double p = ctx->table[i] / total;
            e += -p * log2(p);
        }
    }
    return e;
}


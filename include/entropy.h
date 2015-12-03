/* -*- Mode: c; tab-width: 4; c-basic-offset: 4; indent-tabs-mode: nil; -*- */

#ifndef __ENTROPY_H__
#define __ENTROPY_H__

#include <stddef.h>
#include <stdint.h>


struct entropy_ctx;

size_t entropy_sizeof(void);
void entropy_init(struct entropy_ctx *ctx);
void entropy_update(struct entropy_ctx *ctx, uint8_t *buf, size_t len);
double entropy_current(const struct entropy_ctx *ctx);


#endif

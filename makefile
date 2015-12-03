# libentropy: Shannon entropy

.SUFFIXES: .c .a .o .h
.PHONY: clean all install uninstall clean
.VPATH: ./ ./src ./include

TARGET_BIN=entropy
TARGET_LIB=libentropy.so

SRCS+=src/entropy.c
OBJS+=$(subst .c,.o, $(SRCS))

CFLAGS+=-std=c11
CFLAGS+=-Wall
CFLAGS+=-fPIC
ifeq ($(DEBUG),yes)
  CFLAGS+=-g
  CFLAGS+=-ggdb
else
  CFLAGS+=-O2
  CFLAGS+=-DNDEBUG
endif

INCDIR+=-I./include
LDFLAGS+=-lm


all: $(TARGET_BIN)

$(TARGET_BIN): $(TARGET_LIB) src/main.c
	$(CC) $(CFLAGS) $(DEFS) $(INCDIR) src/main.c -o $@ $(TARGET_LIB) $(LDFLAGS)

$(TARGET_LIB): $(OBJS)
	$(CC) -shared $(CFLAGS) -o $@ $^

install: $(TARGET_BIN) $(TARGET_LIB)
	install -Dm644 include/entropy.h $(DESTDIR)/usr/include/entropy/entropy.h
	install -Dm644 $(TARGET_LIB) $(DESTDIR)/usr/lib/
	install -Dm755 $(TARGET_BIN) $(DESTDIR)/usr/bin/

uninstall:
	rm $(DESTDIR)/usr/include/entropy/entropy.h
	rmdir $(DESTDIR)/usr/include/entropy
	rm $(DESTDIR)/usr/lib/$(TARGET_LIB)
	rm $(DESTDIR)/usr/bin/$(TARGET_BIN)

clean:
	rm -f $(TARGET_BIN) $(TARGET_LIB) $(OBJS)

.c.o:
	$(CC) $(CFLAGS) $(DEFS) $(INCDIR) -c $< -o $@

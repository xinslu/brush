TARGET = brush

CC     = gcc
CFLAGS = -Wall -Wextra -Wsign-conversion -Wpointer-arith -Wcast-qual -Wwrite-strings -Wshadow -Wmissing-prototypes -Wpedantic -Wwrite-strings -g -std=gnu99

LFLAGS = -lpthread

SRCDIR = src
INCDIR = $(SRCDIR)
BINDIR = build

SRC := $(wildcard $(SRCDIR)/*.c)
INC := $(wildcard $(INCDIR)/*.h)

INCFLAGS := $(patsubst %/,-I%,$(dir $(wildcard $(INCDIR)/.)))

.PHONY: debug
debug: CFLAGS += -ggdb -g3 -DDEBUG
debug: $(BINDIR)/$(TARGET)

.PHONY: release
release: CFLAGS += -mtune=native -O2
release: $(BINDIR)/$(TARGET)

$(BINDIR)/$(TARGET): $(SRC) $(INC)
	@mkdir -p $(BINDIR)
	@$(CC) $(CFLAGS) $(INCFLAGS) $(SRC) -o $@ $(LFLAGS)

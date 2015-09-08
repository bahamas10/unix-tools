CFLAGS = -Wall -std=c99
SRC = $(wildcard *.c)
BIN = $(patsubst %.c,%,$(SRC))

all: $(BIN)

clean:
	rm -rf $(BIN)

.PHONY: clean

CFLAGS = -Wall
SRC = $(wildcard *.c)
BIN = $(patsubst %.c,%,$(SRC))

all: $(BIN)

clean:
	rm -rf $(BIN)

.PHONY: clean

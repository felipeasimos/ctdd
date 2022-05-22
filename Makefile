CC=clang
SRC=$(wildcard ./tests/*.c)
TARGET=./tests/test_main

.PHONY: all clean test
all: clean build test
build: clean
	$(CC) $(SRC) -o $(TARGET)
clean:
	@-rm -rf $(TARGET)
test: build
	$(TARGET)

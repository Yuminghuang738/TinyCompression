CC = gcc
CFLAGS = -g -Wall -o0

SRCS = src/bit_io.c src/encode.c src/main.c src/output.c src/statistics.c src/input.c src/decode.c
TARGET = tc

$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) $(SRCS) -o $(TARGET)

clean:
	rm -f $(TARGET)
CC = gcc
CFLAGS = -g -Wall -o0

SRCS = bit_io.c encode.c main.c output.c statistics.c
TARGET = tc

$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) $(SRCS) -o $(TARGET)

clean:
	rm -f $(TARGET)
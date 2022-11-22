CC = gcc
CFLAGS = -Wall -O3
SRCS = $(wildcard *.c)
OBJS = $(SRCS:.c=.o)

TARGET = main

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

clean:
	$(RM) $(TARGET) $(OBJS) *~
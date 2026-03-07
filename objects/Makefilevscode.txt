#this is for the testmodel test.c in vs code, there is one for steem emulator just rename to makefile
CC = clang

CFLAGS = -Wall -Wextra -std=c11

TARGET = test

SRCS = \
	asynch.c \
	card.c \
	cond.c \
	dealer.c \
	deck.c \
	hand.c \
	model.c \
	player.c \
	timer.c \
	testmo.c \
	test.c

OBJS = $(SRCS:.c=.o)

$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET)

%.o: %.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f $(OBJS) $(TARGET)
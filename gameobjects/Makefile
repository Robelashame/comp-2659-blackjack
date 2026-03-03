#this is for the testmodel test.c maybe i shoulda named it better but whatever
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
	testmodel.c \
	test.c

OBJS = $(SRCS:.c=.o)

$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET)

%.o: %.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f $(OBJS) $(TARGET)
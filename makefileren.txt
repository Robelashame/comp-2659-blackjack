# Compiler and flags
CC = cc68x
CFLAGS = -g

# Object files
OBJS = testren.o render.o raster.o font.o model.o player.o dealer.o deck.o hand.o card.o timer.o asynch.o cond.o bmaps.o

# Target executable
TARGET = tst_rend

# Default rule
all: $(TARGET)

# Link object files to create executable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(TARGET)

# Pattern rule to compile .c to .o
%.o: %.c
	$(CC) $(CFLAGS) -c $<

# Clean up build files
.PHONY: clean
clean:
	rm -f $(OBJS) $(TARGET)
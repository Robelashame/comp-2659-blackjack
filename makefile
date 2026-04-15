# Compiler
CC = cc68x

# Flags
CFLAGS = -g

# Source files (EXCLUDING RAST_ASM.S)
SRCS = asynch.c bmaps.c card.c cond.c dealer.c deck.c font.c \
       game.c hand.c handle.c input.c model.c player.c \
       raster.c render.c synch.c time.c timer.c vbl.c

# Object files
OBJS = asynch.o bmaps.o card.o cond.o dealer.o deck.o font.o \
       game.o hand.o handle.o input.o model.o player.o \
       raster.o render.o synch.o time.o timer.o vbl.o \
       RAST_ASM.o VBL_ASM.o

# Output
TARGET = game.prg

# Default rule
all: $(TARGET)

# Link
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

# Compile
.c.o:
	$(CC) $(CFLAGS) -c $<

RAST_ASM.o: RAST_ASM.S
	gen -L2 RAST_ASM.S

VBL_ASM.o: VBL_ASM.S
	gen -L2 VBL_ASM.S

# Clean
clean:
	rm -f *.o $(TARGET)
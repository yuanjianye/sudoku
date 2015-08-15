CROSS_COMPILE=
CC=$(CROSS_COMPILE)gcc
TARGET:=sudoku
CFLAGS=
LDFLAGS=
all:
	$(CC) sudoku.c $(CFLAGS) $(LDFLAGS) -o $(TARGET)
clean:
	rm -rf *.o $(TARGET)

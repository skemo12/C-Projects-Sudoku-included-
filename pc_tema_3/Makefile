CC = gcc
CFLAG = -Wall -Wextra -g
EXE = sudoku
OBJ = sudoku.o

build: $(EXE)

%.o: %.c 
	$(CC) -c -o $@ $< $(CFLAG)

$(EXE): $(OBJ)
	$(CC) $^ $(CFLAG) -o $(EXE)

run:
	./$(EXE)

.PHONY: clean

clean:
	rm -f *.o $(EXE)


CC = gcc
INCLUDE = ./includes/
BINARY = ./build/binary

all: clean compile run

run:
	$(BINARY)

clean:
	rm *.o

compile: main.o algoritmos.o arquivo_csv.o trabalho02.o
	$(CC) -o $(BINARY) main.o algoritmos.o arquivo_csv.o trabalho02.o -W

main.o:
	$(CC) -c ./src/main.c -I $(INCLUDE) -W

algoritmos.o:
	$(CC) -c ./src/algoritmos.c -I $(INCLUDE) -W

arquivo_csv.o:
	$(CC) -c ./src/arquivo_csv.c -I $(INCLUDE) -W

trabalho02.o:
	$(CC) -c ./src/trabalho02.c -I $(INCLUDE) -W

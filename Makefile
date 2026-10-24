CC = gcc
CFLAGS = -std=c11 -Wall -Wextra -Werror -pedantic
SRC = src/main.c src/config.c src/vm.c src/mem.c src/sched.c src/logger.c
TARGET = minihv.exe

all: 

: 
   -o 

clean:
rm -f  minihv_output.jsonl minihv_snapshot.jsonl
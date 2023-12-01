gcc -std=c99 -g -Wall -Wextra ./main.c
valgrind -s --leak-check=yes ./a.out
./a.out
gcc -std=c99 -g ./main.c
valgrind -s --leak-check=yes ./a.out
./a.out
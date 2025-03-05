#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
    int p = 2;
    int m = 5;

    int result = p & 3;
    // printf("%c & %c = %c\n", p, m, result);
    printf("%d & %d = %d\n", p, m, result);
}
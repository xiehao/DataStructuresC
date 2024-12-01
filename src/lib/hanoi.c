#include "hanoi.h"

static void move(char a, char b) { printf("%c -> %c\n", a, b); }

void hanoi(int n, char a, char b, char c) {
    printf("push: %d\n", n);
    if (!n) {
        printf("pop: %d\n", n);
        return;
    }
    hanoi(n - 1, a, c, b);
    move(a, c);
    hanoi(n - 1, b, a, c);
    printf("pop: %d\n", n);
}

void solve_hanoi() {
    int n = 5;
    hanoi(n, 'a', 'b', 'c');
}
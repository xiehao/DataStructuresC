#ifndef HANOI_H
#define HANOI_H

#include <stdio.h>

/**
 * @brief Hanoi processing
 * print all moving steps, given n disks, from a to c, via b
 * @param n the number of disks
 * @param a tower a, the initial station
 * @param b tower b, the transfer station
 * @param c tower c, the destination
 */
extern void hanoi(int n, char a, char b, char c);

extern void solve_hanoi();

#endif // HANOI_H
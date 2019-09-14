/*
There is a list of sorted integers from 1 to n. Starting from left to right, remove the first number and every other number afterward until you reach the end of the list.

Repeat the previous step again, but this time from right to left, remove the right most number and every other number from the remaining numbers.

We keep repeating the steps again, alternating left to right and right to left, until a single number remains.

Find the last number that remains starting with a list of length n.

Example:

Input:
n = 9,
1 2 3 4 5 6 7 8 9
2 4 6 8
2 6
6

Output:
6
*/

#include <stdio.h>

int lastRemainingNumber(int n) {
    int f = 1, d = 1;
    bool left = true;
    while(n > 1) {
        if (left || (n & 0x1) > 0)
            f += d;
        d <<= 1;
        n >>= 1;
        left = !left;
    }
    return f;
}

int main() {
    for(int i = 1; i < 100; i++)
        printf("%d\n", lastRemainingNumber(i));
    getchar();
    return 0;
}

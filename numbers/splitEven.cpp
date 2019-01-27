/*
Write a function to determine if an array of non-negative numbers can be splited evenly.
Example 1:
[1,3]
false

Example 2:
[1,3,4,5,5]
true
*/

#include <stdio.h>

bool possibleSum(int *arr, int siz, int start, int sum) {
    if (start >= siz)
        return false;

    if (arr[start] == sum)
        return true;
        
    return (sum > arr[start] && possibleSum(arr, siz, start + 1, sum - arr[start])) || possibleSum(arr, siz, start + 1, sum);
}

bool splitEven(int *arr, int siz) {
    int r = 0;
    for(int i = 0; i < siz; i++)
        r += arr[i];
    if (r & 0x1)
        return false;
    return possibleSum(arr, siz, 0, r / 2);
}

int main() {
    int arr[] = {1,3,4,2,5,5};
    printf("%d", splitEven(arr, sizeof(arr) / sizeof(arr[0])));
    getchar();
    return 0;
}
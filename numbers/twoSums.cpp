/*
Given an integer array and a number N. Find if there are two integers inside the array 
whose sum equals N.
*/

#include <stdio.h>

void do_qsort(int* arr, int low, int high) {
    if (low >= high)
        return;
    int hi = high + 1, lo = low;
    int item = arr[lo];
    while(true) {
        while(++lo <= high && arr[lo] <= item) ;
        while(--hi > low && arr[hi] >= item) ;
        if (lo < hi) {
            int tmp = arr[lo];
            arr[lo] = arr[hi];
            arr[hi] = tmp;
        }
        else
            break;        
    }
    if (low != hi) {
        arr[low] = arr[hi];
        arr[hi] = item;
    }
    do_qsort(arr, low, hi - 1);
    do_qsort(arr, hi + 1, high);    
}

bool possibleSum(int* arr, int siz, int N) {
    if (siz < 2)
        return false;
    do_qsort(arr, 0, siz - 1);
    if (N > arr[siz - 2] + arr[siz - 1] || N < arr[0] + arr[1])
        return false;
    int lo = 0, hi = siz - 1;
    while(lo < hi) {
        int sum = arr[lo] + arr[hi];
        if (sum == N)
            return true;
        sum < N ? lo++ : hi--;
    }
    return false;
}

int main() {
    int arr[] = {4, 5, 8, 2};
    int N = 11;
    if(possibleSum(arr, sizeof(arr) / sizeof(arr[0]), N))
        printf("it is possible");
    else
        printf("it is not possible");
    getchar();
    return 0;
}
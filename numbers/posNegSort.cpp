/*
Given an array with half of positive numbers and half of negative numbers.
Write an algorithm to sort the array so that each positive number is followed by a negative number.

Example 1:
[1,3,-2,4,5,-6,-9,-2]
output:
[1,-2,3,-6,4,-9,5,-2] or any other resonable outputs would also be accepted.
*/
#include <stdio.h>

void swap(int* arr, int i, int j) {
    int tmp = arr[i];
    arr[i] = arr[j];
    arr[j] = tmp;
}

void sortArray(int *a, int len)
{
    if(len == 0)
        return;
    int j = 0;
    while(j < len && a[j] < 0) j++;
    if (j != 0)
        swap(a, 0, j);
    j = 0;
    for(int i = 1; i < len; i++)
    {
        if(a[i] * a[j] < 0)
        {
            if(i > j + 1)
            {
                swap(a, i, j + 1);         
                j++;
            }
            j++;
        }
    }
}

int main() {
    int arr[] = {-1,3,2,-4,6,-5,-9,2};
    sortArray(arr, sizeof(arr)/sizeof(arr[0]));
    for(auto& d: arr)
        printf("%d\t", d);
    getchar();
    return 0;
}
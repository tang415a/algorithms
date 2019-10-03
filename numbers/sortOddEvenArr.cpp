/*
Given an array A of non-negative integers, half of the integers in A are odd, and half of the integers are even.

Sort the array so that whenever A[i] is odd, i is odd; and whenever A[i] is even, i is even.

Example 1:

Input: [4,2,5,7]
Output: [4,5,2,7]
Explanation: [4,7,2,5], [2,5,4,7], [2,7,4,5] would also have been accepted.
*/

#include <stdio.h>
#include <vector>
using namespace std;

void swap(int *arr, int i, int j)
{
	int tmp = arr[i];
	arr[i] = arr[j];
	arr[j] = tmp;
}

void sortArray(int *a, int len)
{
	if (len == 0)
		return;
	int j = 0;
	for (int i = 0; i < len; i++)
	{
		if (((a[i] + j) & 0x1) == 0)
		{
			if (i > j)
			{
				swap(a, i, j);
				j++;
			}
			j++;
		}
	}
}

int main()
{
	int arr[] = {1, 3, 2, 4, 5, 7, 0, 8};
	sortArray(arr, sizeof(arr) / sizeof(arr[0]));
	for (int &d : arr)
		printf("%d\t", d);
	getchar();
	return 0;
}
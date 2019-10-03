/*
Given an integer array and a number N. Find if there are three integers inside the array 
whose sum equals N.
*/

#include <stdio.h>
#include <memory.h>

void do_qsort(int *arr, int low, int high)
{
	if (low >= high)
		return;
	int hi = high + 1, lo = low;
	int item = arr[lo];
	while (true)
	{
		while (++lo <= high && arr[lo] <= item)
			;
		while (--hi > low && arr[hi] >= item)
			;
		if (lo < hi)
		{
			int tmp = arr[lo];
			arr[lo] = arr[hi];
			arr[hi] = tmp;
		}
		else
			break;
	}
	if (low != hi)
	{
		arr[low] = arr[hi];
		arr[hi] = item;
	}
	do_qsort(arr, low, hi - 1);
	do_qsort(arr, hi + 1, high);
}

bool isPossible(int *arr, int siz, int N)
{
	if (siz < 3)
		return false;
	int min = arr[0], max = arr[0];
	int greaterSiz = 0, lessSiz = 0, equalSiz = 0;
	bool canBeDivided = N % 3 == 0;
	for (int i = 1; i < siz; i++)
	{
		if (arr[i] > max)
			max = arr[i];
		if (arr[i] < min)
			min = arr[i];
		if (arr[i] > N / 3)
			greaterSiz++;
		if (arr[i] < N / 3)
			lessSiz++;
		if (canBeDivided && arr[i] == N / 3)
			equalSiz++;
	}
	if (equalSiz >= 3)
	{
		printf("found %d, %d, %d", N / 3, N / 3, N / 3);
		return true;
	}
	if (lessSiz == 0 || greaterSiz == 0)
		return false;
	if (min * 2 + max > N)
		max = N - min * 2;
	if (max * 2 + min < N)
		min = N - max * 2;
	int *m = new int[max - min + 1];
	memset(m, 0, sizeof(int) * (max - min + 1));
	int *less = new int[lessSiz];
	int *greater = new int[greaterSiz];
	lessSiz = greaterSiz = 0;
	float average = N / 3;
	for (int i = 0; i < siz; i++)
	{
		if (arr[i] >= min && arr[i] <= max)
		{
			if (m[arr[i] - min]++ == 0)
			{
				if (arr[i] > average)
					greater[greaterSiz++] = arr[i];
				else if (arr[i] < average)
					less[lessSiz++] = arr[i];
			}
		}
	}
	do_qsort(less, 0, lessSiz);
	do_qsort(greater, 0, greaterSiz);

	int base = 0;
	for (int i = lessSiz - 1; i >= 0; i--)
	{
		int v = less[i];
		int c = (N - v) >> 1;
		while (base < greaterSiz && greater[base] < c)
			base++;
		for (int j = base; j < greaterSiz; j++)
		{
			int a = N - v - greater[j];
			if (a < v)
				break;
			if (a > greater[j])
				continue;
			if ((a == v && m[a - min] > 1) || (a == greater[j] && m[a - min] > 1) || (a != v && a != greater[j] && m[a - min] > 0))
			{
				printf("found %d, %d, %d", v, a, greater[j]);
				delete[] m, less, greater;
				return true;
			}
		}
	}
	delete[] m, less, greater;
	return false;
}

int main()
{
	int arr[] = {1, 5, 5, 2, 5, 6};
	int N = 15;
	if (!isPossible(arr, sizeof(arr) / sizeof(arr[0]), N))
		printf("Not possible");
	getchar();
	return 0;
}
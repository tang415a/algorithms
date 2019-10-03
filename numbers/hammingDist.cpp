/*
The Hamming distance between two integers is the number of positions at which the corresponding bits are different.

Now your job is to find the total Hamming distance between all pairs of the given numbers.

Example:
Input: 4, 14, 2

Output: 6

Explanation: In binary representation, the 4 is 0100, 14 is 1110, and 2 is 0010 (just
showing the four bits relevant in this case). So the answer will be:
HammingDistance(4, 14) + HammingDistance(4, 2) + HammingDistance(14, 2) = 2 + 2 + 2 = 6.

Note:
Elements of the given array are in the range of 0 to 10^9
Length of the array will not exceed 10^4.
*/

#include <stdio.h>
#include <vector>
using namespace std;

int totalHammingDistance(const vector<int> &nums)
{
	int ones[32] = {0};
	for (auto &n : nums)
	{
		int i = 0, tmp;
		while ((tmp = (1 << i)) <= n)
		{
			if (n & tmp)
				ones[i]++;
			i++;
		}
	}
	int res = 0;
	for (auto &n : ones)
		res += n * (nums.size() - n);
	return res;
}

int main()
{
	printf("%d", totalHammingDistance({4, 14, 2}));
	getchar();
	return 0;
}
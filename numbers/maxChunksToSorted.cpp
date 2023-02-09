/*
You are given an integer array arr of length n that represents a permutation of
the integers in the range [0, n - 1].

We split arr into some number of chunks (i.e., partitions), and individually
sort each chunk. After concatenating them, the result should equal the sorted
array.

Return the largest number of chunks we can make to sort the array.

Example 1:

Input: arr = [4,3,2,1,0]
Output: 1
Explanation:
Splitting into two or more chunks will not return the required result.
For example, splitting into [4, 3], [2, 1, 0] will result in [3, 4, 0, 1, 2],
which isn't sorted.

Example 2:

Input: arr = [1,0,2,3,4]
Output: 4
Explanation:
We can split into two chunks, such as [1, 0], [2, 3, 4].
However, splitting into [1, 0], [2], [3], [4] is the highest number of chunks
possible.


Constraints:

n == arr.length
1 <= n <= 10
0 <= arr[i] < n
All the elements of arr are unique.
*/

#include <iostream>
#include <vector>

using namespace std;

int maxChunksToSorted(const vector<int> &arr) {
  int ans = arr[0] == 0 ? 1 : 0;
  for (int j = arr[0], i = 1, n = arr.size(); i < n; i++) {
    if (j < arr[i])
      j = arr[i];
    if (i == j)
      ans++;
  }
  return ans;
}

int maxChunksToSorted2(const vector<int> &arr) {
  int n = arr.size(), s = 0;
  vector<int> st(n);
  for (int i = 0; i < n; i++) {
    int j = s;
    while (j > 0 && arr[i] < st[j - 1]) {
      --j;
    }
    if (j < s - 1) {
      st[j] = st[s - 1];
      s = j + 1;
    } else if (j == s) {
      st[s++] = arr[i];
    }
  }
  return s;
}

int main() {
  cout << maxChunksToSorted({4, 3, 2, 1, 0}) << endl;
  cout << maxChunksToSorted({1, 0, 2, 3, 4}) << endl;
  cout << maxChunksToSorted({2, 0, 1, 3, 4}) << endl;
  cout << maxChunksToSorted2({4, 3, 2, 1, 0}) << endl;
  cout << maxChunksToSorted2({1, 0, 2, 3, 4}) << endl;
  cout << maxChunksToSorted2({2, 0, 1, 3, 4}) << endl;
  return 0;
}
/*
You are given an integer array arr.

We split arr into some number of chunks (i.e., partitions), and individually
sort each chunk. After concatenating them, the result should equal the sorted
array.

Return the largest number of chunks we can make to sort the array.

Example 1:

Input: arr = [5,4,3,2,1]
Output: 1
Explanation:
Splitting into two or more chunks will not return the required result.
For example, splitting into [5, 4], [3, 2, 1] will result in [4, 5, 1, 2, 3],
which isn't sorted.

Example 2:

Input: arr = [2,1,3,4,4]
Output: 4
Explanation:
We can split into two chunks, such as [2, 1], [3, 4, 4].
However, splitting into [2, 1], [3], [4], [4] is the highest number of chunks
possible.

Constraints:

1 <= arr.length <= 2000
0 <= arr[i] <= 10^8
*/

#include <iostream>
#include <vector>

using namespace std;

int maxChunksToSorted(const vector<int> &arr) {
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

int maxChunksToSorted2(const vector<int> &arr) {
  int n = arr.size();
  vector<int> chunk_max;
  for (int i = 0; i < n; ++i) {
    int v = arr[i];
    int mx = v;
    while (!chunk_max.empty() && chunk_max.back() > v) {
      mx = max(mx, chunk_max.back());
      chunk_max.pop_back();
    }
    chunk_max.push_back(mx);
  }
  return chunk_max.size();
}

int main() {
  cout << maxChunksToSorted({5, 4, 3, 2, 1}) << endl;
  cout << maxChunksToSorted({2, 1, 3, 4, 4}) << endl;
  cout << maxChunksToSorted({4, 1, 3, 5, 4}) << endl;
  return 0;
}
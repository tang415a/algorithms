/*
You are given a binary array nums containing only the integers 0 and 1. Return
the number of subarrays in nums that have more 1's than 0's. Since the answer
may be very large, return it modulo 10^9 + 7.

A subarray is a contiguous sequence of elements within an array.

Example 1:

Input: nums = [0,1,1,0,1]
Output: 9
Explanation:
The subarrays of size 1 that have more ones than zeros are: [1], [1], [1]
The subarrays of size 2 that have more ones than zeros are: [1,1]
The subarrays of size 3 that have more ones than zeros are: [0,1,1], [1,1,0],
[1,0,1]
The subarrays of size 4 that have more ones than zeros are: [1,1,0,1]
The subarrays of size 5 that have more ones than zeros are: [0,1,1,0,1]

Example 2:

Input: nums = [0]
Output: 0
Explanation:
No subarrays have more ones than zeros.

Example 3:

Input: nums = [1]
Output: 1
Explanation:
The subarrays of size 1 that have more ones than zeros are: [1]


Constraints:

1 <= nums.length <= 10^5
0 <= nums[i] <= 1
*/
#include <iostream>
#include <vector>

using namespace std;

int countOfSubArrays(const vector<int> &arr) {
  int n = arr.size();
  vector<int> c(n + 1, 0);
  for (int i = 0; i < n; i++) {
    if (arr[i] == 1)
      c[i + 1] = c[i] + 1;
    else
      c[i + 1] = c[i] - 1;
  }

  int ans = 0;
  for (int j = 0; j < n; j++) {
    int i = j + 1;
    while (i <= n) {
      int d = c[i] - c[j];
      if (d > 0) {
        ans += min(d, n - i + 1);
        i += d;
      } else if (d == 0) {
        i++;
      } else {
        i -= d;
      }
    }
  }
  return ans;
}

int countOfSubArrays2(const vector<int> &arr) {
  int n = arr.size();
  vector<int> c(n + 1, 0);
  for (int i = 0; i < n; i++) {
    if (arr[i] == 1)
      c[i + 1] = c[i] + 1;
    else
      c[i + 1] = c[i] - 1;
  }

  int ans = 0;
  for (int j = 0; j < n; j++) {
    for (int i = j + 1; i <= n; i++) {
        if (c[i] > c[j])
            ans++;
    }
  }
  return ans;
}

#include <time.h>
int main() {
  cout << countOfSubArrays({0, 1, 1, 0, 1}) << endl;
  cout << countOfSubArrays({0}) << endl;
  cout << countOfSubArrays({1}) << endl;
  srand((unsigned int)time(NULL));
  vector<int> arr(100000);
  for (int i = 0; i < 100000; i++) {
    arr[i] = rand() % 2;
  }
  cout << countOfSubArrays(arr) << endl;
  cout << countOfSubArrays2(arr) << endl;
  return 0;
}
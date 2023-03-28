/*
Given an integer array nums, reorder it such that nums[0] < nums[1] > nums[2] <
nums[3]....

You may assume the input array always has a valid answer.

Example 1:

Input: nums = [1,5,1,1,6,4]
Output: [1,6,1,5,1,4]
Explanation: [1,4,1,5,1,6] is also accepted.

Example 2:

Input: nums = [1,3,2,2,3,1]
Output: [2,3,1,3,1,2]

Constraints:

1 <= nums.length <= 5 * 10^4
0 <= nums[i] <= 5000
It is guaranteed that there will be an answer for the given input nums.
*/

#include <iostream>
#include <vector>

using namespace std;

#include <algorithm>

// key findings: the array should have n / 2 high waves and n - n / 2 low waves
// thus after sort the last element nums[n - 1] that is the largest should be
// greater than the nums[n - 1 - n / 2]
// (n - 1) / 2        ==        n - 1 - n / 2
// n is even                    n / 2 - 1 = (n - 1) / 2
// n is odd,                    (n - 1) / 2
void wiggleSort1(vector<int> &nums) {
  const int n = nums.size();
  int *tmp = new int[n];
  sort(nums.begin(), nums.end());
  int left = (n - 1) / 2, right = n - 1;
  for (int i = 0; i < n; i++) {
    if (i & 0x1 == 0) {
      tmp[i] = nums[left--];
    } else {
      tmp[i] = nums[right--];
    }
  }
  for (int i = 0; i < n; i++) {
    nums[i] = tmp[i];
  }
  delete[] tmp;
}

void wiggleSort0(vector<int> &nums) {
  auto sorted = nums;
  sort(sorted.begin(), sorted.end());

  int left = (sorted.size() - 1) / 2, right = sorted.size() - 1;

  bool flag = true;
  for (int i = 0; i < nums.size(); i++) {
    nums[i] = (flag) ? sorted[left--] : sorted[right--];
    flag = !flag;
  }
}

// partition based on the right of nums
int partition(int *nums, int left, int right) {
  int x = nums[right];
  int i = left;
  int j = right - 1;
  while (i <= j) {
    if (nums[i] <= x) {
      i++;
    } else {
      if (nums[j] > x) {
        j--;
      } else {
        int tmp = nums[i];
        nums[i] = nums[j];
        nums[j] = tmp;
        i++;
        j--;
      }
    }
  }
  nums[right] = nums[i];
  nums[i] = x;
  return i;
}

// select the ith element with elements partially sort (similar to quick sort)
int quickSelect(int *nums, int left, int right, int i) {
  if (left == right) {
    return nums[left];
  }
  // move nums[right] to its right pos: qth element from 0
  int q = partition(nums, left, right);
  int k = q - left + 1; // nums[q] is the kth element from left
  if (i == k) {
    return nums[q];
  } else if (i < k) {
    return quickSelect(nums, left, q - 1, i);
  } else {
    return quickSelect(nums, q + 1, right, i - k);
  }
}

int index(int i, int n) {
  if (i < n / 2) {
    return i * 2 + 1;
  } else {
    return (i - n / 2) * 2;
  }
}

void wiggleSort(vector<int> &nums) {
  const int n = nums.size();
  // median is the (n + 1) / 2 th element in the array
  int median = quickSelect(&nums[0], 0, n - 1, (n + 1) / 2);
  // now elements before (n + 1) / 2 <= median, elements after (n + 1) / 2 >=
  // median. next we check the elements at even pos before (n + 1) / 2 and at
  // odd pos after (n + 1) / 2
  int i = 0, j = 0, k = n - 1;
  while (i <= k) {
    int it = index(i, n), jt = index(j, n), kt = index(k, n);
    if (nums[it] > median) {
      // swap nums at it, jt; move greater element to the jt (even pos)
      int tmp = nums[it];
      nums[it] = nums[jt];
      nums[jt] = tmp;
      i++;
      j++;
    } else if (nums[it] < median) {
      // swap nums at it, kt; move smaller element to the kt (odd pos)
      int tmp = nums[it];
      nums[it] = nums[kt];
      nums[kt] = tmp;
      k--;
    } else {
      // equal to median: increase i only.
      // the element could be used at both odd and even pos
      // keep the element as it is
      i++;
    }
  }
}

void wiggleSort2(vector<int> &nums) {
  int count[5001];
  memset(count, 0, sizeof(int) * 5001);
  for (int i : nums) {
    count[i]++;
  }

  // find the (n + 1) / 2 th element starting from 1, i.e. (n - 1) / 2 th
  // element starting from 0
  int j = 0, k = 0, n = nums.size(), l = (n + 1) / 2;
  for (; j < 5001 && k + count[j] <= l; j++) {
    k += count[j];
    if (k == l)
      break;
  }

  int o = 0;
  if (k < l) {
    o = l - k;  // should repeat j o times from l
  }
  // when nums has odd elements, it has l - 1 pairs
  if (n & 0x1) {
    l--;
  }

  for (int x = 0, i = 5000; x < l; x++) {
    while (count[j] == 0)
      j--;
    count[j]--;
    while (count[i] == 0)
      i--;
    count[i]--;
    nums[2 * x] = j;
    nums[2 * x + 1] = i;
    if (o > 0 && --o == 0) {
      j--;
    }
  }
  // when nums has odd elements, the last element should be low wave
  if (n & 0x1) {
    while (count[j] == 0)
      j--;
    nums[n - 1] = j;
  }
}

int main() {
  vector<int> nums = {6, 5, 1, 1, 1, 4}; //{1, 5, 1, 1, 6, 4};
  wiggleSort(nums);
  char *comma = "";
  for (int i : nums) {
    cout << comma << i;
    comma = ",";
  }
  cout << endl;
  nums = {1, 3, 2, 2, 3, 1};
  wiggleSort(nums);
  comma = "";
  for (int i : nums) {
    cout << comma << i;
    comma = ",";
  }
  cout << endl;
  nums = {1, 3, 2, 2, 3, 1, 2};
  wiggleSort(nums);
  comma = "";
  for (int i : nums) {
    cout << comma << i;
    comma = ",";
  }
  cout << endl;
  nums = {1, 3, 2};
  wiggleSort(nums);
  comma = "";
  for (int i : nums) {
    cout << comma << i;
    comma = ",";
  }
  cout << endl;
  nums = {4, 5, 5, 6};
  wiggleSort(nums);
  comma = "";
  for (int i : nums) {
    cout << comma << i;
    comma = ",";
  }
  cout << endl;
  return 0;
}
/*
Alice had a 0-indexed array arr consisting of n positive integers. She chose an
arbitrary positive integer k and created two new 0-indexed integer arrays lower
and higher in the following manner:

lower[i] = arr[i] - k, for every index i where 0 <= i < n
higher[i] = arr[i] + k, for every index i where 0 <= i < n
Unfortunately, Alice lost all three arrays. However, she remembers the integers
that were present in the arrays lower and higher, but not the array each integer
belonged to. Help Alice and recover the original array.

Given an array nums consisting of 2n integers, where exactly n of the integers
were present in lower and the remaining in higher, return the original array
arr. In case the answer is not unique, return any valid array.

Note: The test cases are generated such that there exists at least one valid
array arr.

Example 1:

Input: nums = [2,10,6,4,8,12]
Output: [3,7,11]
Explanation:
If arr = [3,7,11] and k = 1, we get lower = [2,6,10] and higher = [4,8,12].
Combining lower and higher gives us [2,6,10,4,8,12], which is a permutation of
nums. Another valid possibility is that arr = [5,7,9] and k = 3. In that case,
lower = [2,4,6] and higher = [8,10,12].

Example 2:

Input: nums = [1,1,3,3]
Output: [2,2]
Explanation:
If arr = [2,2] and k = 1, we get lower = [1,1] and higher = [3,3].
Combining lower and higher gives us [1,1,3,3], which is equal to nums.
Note that arr cannot be [1,3] because in that case, the only possible way to
obtain [1,1,3,3] is with k = 0. This is invalid since k must be positive.

Example 3:

Input: nums = [5,435]
Output: [220]
Explanation:
The only possible combination is arr = [220] and k = 215. Using them, we get
lower = [5] and higher = [435].

Constraints:

2 * n == nums.length
1 <= n <= 1000
1 <= nums[i] <= 10^9
The test cases are generated such that there exists at least one valid array
arr.
*/

#include <algorithm>
#include <iostream>
#include <set>
#include <vector>

using namespace std;

vector<int> recoverArray(const vector<int> &nums) {
  multiset<int> s;
  const int n = nums.size(), h = n / 2;
  for (int i = 0; i < n; i++) {
    s.insert(nums[i]);
  }
  vector<int> ans(h);
  int j = 0;
  ans[j++] = *s.begin();
  s.erase(s.begin());
  int t = *s.begin(), d2 = t - ans[0];
  while (j < h) {
    s.erase(s.begin());
    if (d2 == 0 || (d2 & 0x1)) {
      ans[j++] = t;
      t = *s.begin();
      d2 = t - ans[0];
      continue;
    }
    auto c = s;
    // first try with the collected lowers
    int i = 1;
    for (; i < j; i++) {
      auto iter = c.find(ans[i] + d2);
      if (iter == c.end()) {
        ans[j++] = t;
        t = *s.begin();
        d2 = t - ans[0];
        break;
      }
      c.erase(iter);
    }
    // then try with the new coming lowers
    if (i == j) {
      int k = j;
      while (k < h) {
        int a = *c.begin();
        auto iter = c.find(a + d2);
        if (iter == c.end()) {
          ans[j++] = t;
          t = *s.begin();
          d2 = t - ans[0];
          break;
        }
        ans[k++] = a;
        c.erase(c.begin());
        c.erase(iter);
      }
      if (k == h) // found all the lowers
        break;
    }
  }
  d2 >>= 1;
  for (int &i : ans) {
    i += d2;
  }
  return ans;
}

// a second better approach
#include <unordered_set>
vector<int> recoverArray2(const vector<int> &input) {
  auto nums = input;
  int n = nums.size();
  // find all possible k
  unordered_set<long> ks;
  for (int i = 1; i < n; i++) {
    long sum = nums[i] + nums[0];
    if (!(sum & 1))
      ks.insert(max(nums[0], nums[i]) - (sum >> 1));
  }
  sort(nums.begin(), nums.end());

  // iterate all possible k and use two pointers to check if it works
  vector<int> ans;
  for (auto k : ks) {
    if (!k)
      continue;

    long k2 = k << 1;
    // find the start position of upper to nums[0]
    int upperi =
        lower_bound(nums.begin(), nums.end(), nums[0] + k2) - nums.begin();
    if (upperi == n || nums[upperi] != nums[0] + k2)
      continue; // no such upper

    bool used[2000] = {};
    used[0] = used[upperi++] = true;
    ans.push_back(nums[0] + k);

    for (int loweri = 1; upperi < n; loweri++) {
      if (used[loweri])
        continue;

      long upper = nums[loweri] + k2;
      while (upperi < n && (upper > nums[upperi] || used[upperi]))
        upperi++;

      if (upperi == n || upper != nums[upperi])
        break; // no such upper

      used[upperi++] = true;
      ans.push_back(nums[loweri] + k);
    }

    if (ans.size() == (n >> 1))
      break; // found all of the original array

    ans.clear();
  }
  return ans;
}

int main() {
  vector<int> r = recoverArray({2, 10, 6, 4, 8, 12});
  for (int i : r) {
    cout << i << " ";
  }
  cout << endl;
  r = recoverArray({1, 1, 3, 3});
  for (int i : r) {
    cout << i << " ";
  }
  cout << endl;
  r = recoverArray({5, 435});
  for (int i : r) {
    cout << i << " ";
  }
  cout << endl;
  // use the second approach
  r = recoverArray2({2, 10, 6, 4, 8, 12});
  for (int i : r) {
    cout << i << " ";
  }
  cout << endl;
  r = recoverArray2({1, 1, 3, 3});
  for (int i : r) {
    cout << i << " ";
  }
  cout << endl;
  r = recoverArray2({5, 435});
  for (int i : r) {
    cout << i << " ";
  }
  cout << endl;
  return 0;
}
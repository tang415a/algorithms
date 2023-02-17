/*
Given an integer array nums and an integer k, return the k most frequent
elements. You may return the answer in any order.

Example 1:

Input: nums = [1,1,1,2,2,3], k = 2
Output: [1,2]

Example 2:

Input: nums = [1], k = 1
Output: [1]


Constraints:

1 <= nums.length <= 10^5
-10^4 <= nums[i] <= 10^4
k is in the range [1, the number of unique elements in the array].
It is guaranteed that the answer is unique.


Follow up: Your algorithm's time complexity must be better than O(n log n),
where n is the array's size.
*/
#include <iostream>
#include <map>
#include <vector>

using namespace std;
vector<int> topKFrequent(const vector<int> &nums, int k) {
  int n = nums.size(), h = 0;
  vector<int> frequency(n, 0);
  map<int, int> m1, m2;
  for (int i = 0; i < n; i++) {
    auto it = m1.find(nums[i]);
    if (it != m1.end()) {
      frequency[it->second]++;
    } else {
      m1.insert(make_pair(nums[i], h));
      m2.insert(make_pair(h, nums[i]));
      frequency[h++] = 1;
    }
  }
  bool ascending = k > h / 2;
  int l = ascending ? h - k : k, x = h;
  for (int j = 0; j < l; j++) {
    int i = x / 2;
    while (--i >= 0) {
      int mChild = 2 * i + 1;
      if (mChild + 1 < x) {
        if (ascending) {
          if (frequency[mChild + 1] < frequency[mChild]) {
            mChild++;
          }
        } else {
          if (frequency[mChild + 1] > frequency[mChild]) {
            mChild++;
          }
        }
      }
      if (ascending) {
        if (frequency[i] > frequency[mChild]) {
          swap(frequency[i], frequency[mChild]);
          swap(m2[i], m2[mChild]);
        }
      } else {
        if (frequency[i] < frequency[mChild]) {
          swap(frequency[i], frequency[mChild]);
          swap(m2[i], m2[mChild]);
        }
      }
    }
    --x;
    swap(frequency[0], frequency[x]);
    swap(m2[0], m2[x]);
  }
  frequency.resize(k);
  int base = ascending ? 0 : h - k;
  for (int i = 0; i < k; i++) {
    frequency[i] = m2[base + i];
  }
  return frequency;
}

#include <queue>
vector<int> topKFrequent2(const vector<int> &nums, int k) {
  int n = nums.size(), x = 0;
  vector<int> f(n, 0);
  map<int, int> m, r;
  for (int i = 0; i < n; i++) {
    auto it = m.find(nums[i]);
    if (it != m.end()) {
      f[it->second]++;
    } else {
      m.insert(make_pair(nums[i], x));
      r.insert(make_pair(x, nums[i]));
      f[x++] = 1;
    }
  }
  priority_queue<vector<int>> pq;
  for (int i = 0; i < x; i++) {
    pq.push(vector<int>{-f[i], r[i]});
    while (pq.size() > k) {
      pq.pop();
    }
  }
  f.resize(k);
  for (int i = 0; i < k; i++) {
    f[i] = pq.top().back();
    pq.pop();
  }
  return f;
}

int main() {
  auto r = topKFrequent({1, 1, 1, 2, 2, 3}, 2);
  for (int i : r) {
    cout << i << " ";
  }
  cout << endl;
  r = topKFrequent({1}, 1);
  for (int i : r) {
    cout << i << " ";
  }
  cout << endl;
  r = topKFrequent({1, 1, 5, 5, 7, 6, 0, 1, 0, 2, 2, 0, 3}, 2);
  for (int i : r) {
    cout << i << " ";
  }
  cout << endl;
  r = topKFrequent({1, 1, 4, 5, 4, 5, 7, 5, 6, 5, 0, 1, 0, 2, 2, 2, 0, 2, 3, 2},
                   2);
  for (int i : r) {
    cout << i << " ";
  }
  cout << endl;
  {
    cout << "=====================" << endl;
    auto r = topKFrequent2({1, 1, 1, 2, 2, 3}, 2);
    for (int i : r) {
      cout << i << " ";
    }
    cout << endl;
    r = topKFrequent2({1}, 1);
    for (int i : r) {
      cout << i << " ";
    }
    cout << endl;
    r = topKFrequent2({1, 1, 5, 5, 7, 6, 0, 1, 0, 2, 2, 0, 3}, 2);
    for (int i : r) {
      cout << i << " ";
    }
    cout << endl;
    r = topKFrequent2(
        {1, 1, 4, 5, 4, 5, 7, 5, 6, 5, 0, 1, 0, 2, 2, 2, 0, 2, 3, 2}, 2);
    for (int i : r) {
      cout << i << " ";
    }
    cout << endl;
  }
  return 0;
}
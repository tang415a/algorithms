/*
An integer array original is transformed into a doubled array changed by
appending twice the value of every element in original, and then randomly
shuffling the resulting array.

Given an array changed, return original if changed is a doubled array. If
changed is not a doubled array, return an empty array. The elements in original
may be returned in any order.

Example 1:

Input: changed = [1,3,4,2,6,8]
Output: [1,3,4]
Explanation: One possible original array could be [1,3,4]:
- Twice the value of 1 is 1 * 2 = 2.
- Twice the value of 3 is 3 * 2 = 6.
- Twice the value of 4 is 4 * 2 = 8.
Other original arrays could be [4,3,1] or [3,1,4].

Example 2:

Input: changed = [6,3,0,1]
Output: []
Explanation: changed is not a doubled array.

Example 3:

Input: changed = [1]
Output: []
Explanation: changed is not a doubled array.

Constraints:

1 <= changed.length <= 10^5
0 <= changed[i] <= 10^5
*/
#include <iostream>
#include <set>
#include <vector>

using namespace std;

vector<int> findOriginalArray(const vector<int> &changed) {
  int m = changed.size();
  if (m & 0x1)
    return vector<int>();
  multiset<int> s;
  for (int i : changed) {
    s.insert(i);
  }
  int n = m >> 1, i = 0;
  vector<int> ans(n);
  while (i < n) {
    int top = *s.begin();
    ans[i++] = top;
    s.erase(s.begin());
    auto it = s.find(2 * top);
    if (it == s.end()) {
      ans.clear();
      break;
    }
    s.erase(it);
  }
  return ans;
}

int main() {
  auto r = findOriginalArray({1, 3, 4, 2, 6, 8});
  for (int i : r) {
    cout << i << " ";
  }
  cout << endl;
  r = findOriginalArray({6, 3, 0, 1});
  for (int i : r) {
    cout << i << " ";
  }
  cout << endl;
  r = findOriginalArray({1});
  for (int i : r) {
    cout << i << " ";
  }
  cout << endl;
  return 0;
}
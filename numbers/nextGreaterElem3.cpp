/*
You are given a 0-indexed array of non-negative integers nums. For each integer
in nums, you must find its respective second greater integer.

The second greater integer of nums[i] is nums[j] such that:

j > i
nums[j] > nums[i]
There exists exactly one index k such that nums[k] > nums[i] and i < k < j.
If there is no such nums[j], the second greater integer is considered to be -1.

For example, in the array [1, 2, 4, 3], the second greater integer of 1 is 4, 2
is 3, and that of 3 and 4 is -1. Return an integer array answer, where answer[i]
is the second greater integer of nums[i].

Example 1:

Input: nums = [2,4,0,9,6]
Output: [9,6,6,-1,-1]
Explanation:
0th index: 4 is the first integer greater than 2, and 9 is the second integer
greater than 2, to the right of 2. 1st index: 9 is the first, and 6 is the
second integer greater than 4, to the right of 4. 2nd index: 9 is the first, and
6 is the second integer greater than 0, to the right of 0. 3rd index: There is
no integer greater than 9 to its right, so the second greater integer is
considered to be -1. 4th index: There is no integer greater than 6 to its right,
so the second greater integer is considered to be -1. Thus, we return
[9,6,6,-1,-1].

Example 2:

Input: nums = [3,3]
Output: [-1,-1]
Explanation:
We return [-1,-1] since neither integer has any integer greater than it.

Constraints:

1 <= nums.length <= 10^5
0 <= nums[i] <= 10^9
*/

#include <iostream>
#include <vector>

using namespace std;

#include <set>
vector<int> secondGreaterElement(const vector<int> &nums) {
  const int n = nums.size();
  vector<int> res(n, -1);
  auto compare = [&nums](int i, int j) { return nums[i] < nums[j]; };
  multiset<int, decltype(compare)> s(compare);
  for (int i = 0; i < n; i++) {
    if (!s.empty()) {
      auto it = s.upper_bound(i);
      while (it != s.begin()) {
        --it;
        if (nums[*it] < nums[i]) {
          if (res[*it] == -2) {
            res[*it] = nums[i];
            it = s.erase(it);
          } else {
            res[*it] = -2;
          }
        }
      }
    }
    s.insert(i);
  }
  for (int i : s) {
    res[i] = -1;
  }
  return res;
}

// a better solution
#include <queue>
#include <stack>

using pii = pair<int, int>;
vector<int> secondGreaterElement2(const vector<int> &nums) {
  stack<int> stk;
  priority_queue<pii, vector<pii>, greater<pii>> q; // makes smaller elems top
  int n = nums.size();
  vector<int> ans(n, -1);
  for (int i = 0; i < n; ++i) {
    const int &v = nums[i];
    // priority queue yields the second greater element
    while (!q.empty() && q.top().first < v) {
      ans[q.top().second] = v;
      q.pop();
    }
    // stk is a decreasing (not strictly) stack - first greater element
    while (!stk.empty() && nums[stk.top()] < v) {
      q.push({nums[stk.top()], stk.top()});
      stk.pop();
    }
    stk.push(i);
  }
  return ans;
}

constexpr int MAX = 100010;
constexpr int INF = 0x3F3F3F3F;

pii stk1[MAX], stk2[MAX], stk3[MAX];

vector<int> secondGreaterElement3(const vector<int> &nums) {
  int n = nums.size(), p = 0, q = 0, r = 0;
  vector<int> ret(n, -1);
  stk1[++p] = make_pair(-1, INF);
  stk2[++q] = make_pair(-1, INF);
  for (int i = 0; i < n; ++i) {
    int x = nums[i];
    for (; x > stk2[q].second; --q) {
      ret[stk2[q].first] = x;
    }
    // push the elements less than x in stack 1 to stack 3
    for (; x > stk1[p].second; --p) {
      stk3[++r] = stk1[p]; // increasing
    }
    stk1[++p] = make_pair(i, x); // push to stack 1
    // stk1 is a decreasing stack
    // stk2 is an increasing stack (any element less than x would be popped at
    // Ln. 116 - 118, now push the elements greater than x by the code below)
    for (; r > 0; --r) {
      stk2[++q] = stk3[r];
    }
  }
  return ret;
}

int main() {
  auto r = secondGreaterElement({2, 4, 0, 9, 6});
  char *s = "";
  for (int i : r) {
    cout << s << i;
    s = ", ";
  }
  cout << endl;
  r = secondGreaterElement({3, 3});
  s = "";
  for (int i : r) {
    cout << s << i;
    s = ", ";
  }
  cout << endl;
  r = secondGreaterElement({1, 17, 18, 0, 18, 10, 20, 0});
  s = "";
  for (int i : r) {
    cout << s << i;
    s = ", ";
  }
  cout << endl;
  r = secondGreaterElement({3, 11, 19, 6, 4, 6, 14, 1, 11, 9});
  s = "";
  for (int i : r) {
    cout << s << i;
    s = ", ";
  }
  cout << endl;

  r = secondGreaterElement2({2, 4, 0, 9, 6});
  s = "";
  for (int i : r) {
    cout << s << i;
    s = ", ";
  }
  cout << endl;
  r = secondGreaterElement2({3, 3});
  s = "";
  for (int i : r) {
    cout << s << i;
    s = ", ";
  }
  cout << endl;
  r = secondGreaterElement2({1, 17, 18, 0, 18, 10, 20, 0});
  s = "";
  for (int i : r) {
    cout << s << i;
    s = ", ";
  }
  cout << endl;
  r = secondGreaterElement2({3, 11, 19, 6, 4, 6, 14, 1, 11, 9});
  s = "";
  for (int i : r) {
    cout << s << i;
    s = ", ";
  }
  cout << endl;

  r = secondGreaterElement3({2, 4, 0, 9, 6});
  s = "";
  for (int i : r) {
    cout << s << i;
    s = ", ";
  }
  cout << endl;
  r = secondGreaterElement3({3, 3});
  s = "";
  for (int i : r) {
    cout << s << i;
    s = ", ";
  }
  cout << endl;
  r = secondGreaterElement3({1, 17, 18, 0, 18, 10, 20, 0});
  s = "";
  for (int i : r) {
    cout << s << i;
    s = ", ";
  }
  cout << endl;
  r = secondGreaterElement3({3, 11, 19, 6, 4, 6, 14, 1, 11, 9});
  s = "";
  for (int i : r) {
    cout << s << i;
    s = ", ";
  }
  cout << endl;
  return 0;
}
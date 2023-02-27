/*
You are given two 0-indexed integer arrays nums1 and nums2, each of size n, and
an integer diff. Find the number of pairs (i, j) such that:

0 <= i < j <= n - 1 and
nums1[i] - nums1[j] <= nums2[i] - nums2[j] + diff.
Return the number of pairs that satisfy the conditions.

Example 1:

Input: nums1 = [3,2,5], nums2 = [2,2,1], diff = 1
Output: 3
Explanation:
There are 3 pairs that satisfy the conditions:
1. i = 0, j = 1: 3 - 2 <= 2 - 2 + 1. Since i < j and 1 <= 1, this pair satisfies
the conditions.
2. i = 0, j = 2: 3 - 5 <= 2 - 1 + 1. Since i < j and -2 <= 2, this pair
satisfies the conditions.
3. i = 1, j = 2: 2 - 5 <= 2 - 1 + 1. Since i < j and -3 <= 2, this pair
satisfies the conditions. Therefore, we return 3.

Example 2:

Input: nums1 = [3,-1], nums2 = [-2,2], diff = -1
Output: 0
Explanation:
Since there does not exist any pair that satisfies the conditions, we return 0.

Constraints:

n == nums1.length == nums2.length
2 <= n <= 10^5
-10^4 <= nums1[i], nums2[i] <= 10^4
-10^4 <= diff <= 10^4
*/

#include <iostream>
#include <vector>

using namespace std;

struct TreeNode {
  int val;
  int cnt;
  TreeNode *left = nullptr, *right = nullptr;
  TreeNode(int v, int c = 1) : val(v), cnt(c) {}
};

void clear(TreeNode *r) {
  if (r == nullptr)
    return;
  clear(r->left);
  clear(r->right);
  delete r;
}

void insert(TreeNode *r, int val) {
  if (val < r->val) {
    r->cnt++;
    if (r->left)
      insert(r->left, val);
    else
      r->left = new TreeNode(val);
  } else if (val > r->val) {
    if (r->right)
      insert(r->right, val);
    else
      r->right = new TreeNode(val);
  } else {
    r->cnt++;
  }
}

long long visit(TreeNode *r, int val) {
  if (r->val <= val) {
    if (r->right == nullptr)
      return r->cnt;
    return visit(r->right, val) + static_cast<long long>(r->cnt);
  }
  if (r->left == nullptr)
    return 0;
  return visit(r->left, val);
}

long long numberOfPairs(const vector<int> &nums1, const vector<int> &nums2,
                        int diff) {
  TreeNode *r = new TreeNode(nums1[0] - nums2[0]);
  long long ans = 0;
  for (int i = 1, n = nums1.size(); i < n; i++) {
    int t = nums1[i] - nums2[i];
    ans += visit(r, t + diff);
    insert(r, t);
  }
  clear(r);
  return ans;
}

struct FenwickTree {
  int sz;
  static constexpr int N = 80010;
  int tr[N];

  int low_bit(int x) { return x & -x; }

  int query(int x) {
    int res = 0;
    while (x) {
      res += tr[x];
      x -= low_bit(x);
    }
    return res;
  }

  void update(int x, int dt) {
    while (x <= sz) {
      tr[x] += dt;
      x += low_bit(x);
    }
  }

  long long numberOfPairs(vector<int> &nums1, vector<int> &nums2, int diff) {
    int n = (int)nums1.size();
    sz = N - 1;
    for (int i = 0; i < n; i++)
      nums1[i] -= nums2[i];
    memset(tr, 0, sizeof tr);
    long long res = 0;
    for (int i = 0; i < n; i++) {
      // remap the data to positive numbers
      res += query(nums1[i] + 40000 + diff);
      update(nums1[i] + 40000, 1);
    }
    return res;
  }
};

long long numberOfPairs2(vector<int> &nums1, vector<int> &nums2, int diff) {
  return FenwickTree().numberOfPairs(nums1, nums2, diff);  
}

int main() {
  cout << numberOfPairs({3, 2, 5}, {2, 2, 1}, 1) << endl;
  cout << numberOfPairs({3, -1}, {-2, 2}, -1) << endl;
  {
    vector<int> nums1 = {3, 2, 5}, nums2 = {2, 2, 1};
    cout << numberOfPairs2(nums1, nums2, 1) << endl;
    nums1 = {3, -1};
    nums2 = {-2, 2};
    cout << numberOfPairs2(nums1, nums2, -1) << endl;
  }
  return 0;
}
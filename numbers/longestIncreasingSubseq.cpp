/*
You are given an integer array nums and an integer k.

Find the longest subsequence of nums that meets the following requirements:

The subsequence is strictly increasing and
The difference between adjacent elements in the subsequence is at most k.
Return the length of the longest subsequence that meets the requirements.

A subsequence is an array that can be derived from another array by deleting
some or no elements without changing the order of the remaining elements.

Example 1:

Input: nums = [4,2,1,4,3,4,5,8,15], k = 3
Output: 5
Explanation:
The longest subsequence that meets the requirements is [1,3,4,5,8].
The subsequence has a length of 5, so we return 5.
Note that the subsequence [1,3,4,5,8,15] does not meet the requirements because
15 - 8 = 7 is larger than 3.

Example 2:

Input: nums = [7,4,5,1,8,12,4,7], k = 5
Output: 4
Explanation:
The longest subsequence that meets the requirements is [4,5,8,12].
The subsequence has a length of 4, so we return 4.

Example 3:

Input: nums = [1,5], k = 1
Output: 1
Explanation:
The longest subsequence that meets the requirements is [1].
The subsequence has a length of 1, so we return 1.


Constraints:

1 <= nums.length <= 10^5
1 <= nums[i], k <= 10^5
*/

#include <iostream>
#include <set>
#include <vector>

using namespace std;

struct TreeNode {
  int val;
  int count;
  TreeNode *left;
  TreeNode *right;
  TreeNode(int x, int c = 1)
      : val(x), left(nullptr), right(nullptr), count(c) {}
};

void clear(TreeNode *r) {
  if (r == nullptr)
    return;
  clear(r->left);
  clear(r->right);
  delete r;
}

int visit(TreeNode *r, int val, int k, int &m) {
  int count = 1;
  if (r->val < val) {
    if (val <= r->val + k) {
      count = r->count + 1;
      m = max(count, m);
    }
    if (r->right) {
      count = max(count, visit(r->right, val, k, m));
      m = max(count, m);
    }
  }
  if (r->left) {
    count = max(count, visit(r->left, val, k, m));
    m = max(count, m);
  }
  return count;
}

void insert(TreeNode *r, int val, int c) {
  if (val == r->val) {
    if (c > r->count) {
      r->count = c;
    }
    return;
  }
  if (val < r->val) {
    if (r->left == nullptr) {
      r->left = new TreeNode(val, c);
      return;
    }
    insert(r->left, val, c);
  } else {
    if (r->right == nullptr) {
      r->right = new TreeNode(val, c);
      return;
    }
    insert(r->right, val, c);
  }
}

int lengthOfLIS(const vector<int> &nums, int k) {
  TreeNode *root = new TreeNode(nums[0]);
  int ans = 1;
  for (int i = 1, n = nums.size(); i < n; i++) {
    insert(root, nums[i], visit(root, nums[i], k, ans));
  }
  clear(root);
  return ans;
}

int main() {
  cout << lengthOfLIS({4, 2, 1, 4, 3, 4, 5, 8, 15}, 3) << endl;
  cout << lengthOfLIS({7, 4, 5, 1, 8, 12, 4, 7}, 5) << endl;
  cout << lengthOfLIS({1, 5}, 1) << endl;
  cout << lengthOfLIS({1, 5, 7, 8, 9}, 1) << endl;
  cout << lengthOfLIS({1, 6, 5, 7, 8, 9}, 4) << endl;
  return 0;
}
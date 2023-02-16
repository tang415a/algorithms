/*
Given an integer array nums, return the number of reverse pairs in the array.

A reverse pair is a pair (i, j) where:

0 <= i < j < nums.length and
nums[i] > 2 * nums[j].


Example 1:

Input: nums = [1,3,2,3,1]
Output: 2
Explanation: The reverse pairs are:
(1, 4) --> nums[1] = 3, nums[4] = 1, 3 > 2 * 1
(3, 4) --> nums[3] = 3, nums[4] = 1, 3 > 2 * 1
Example 2:

Input: nums = [2,4,3,5,1]
Output: 3
Explanation: The reverse pairs are:
(1, 4) --> nums[1] = 4, nums[4] = 1, 4 > 2 * 1
(2, 4) --> nums[2] = 3, nums[4] = 1, 3 > 2 * 1
(3, 4) --> nums[3] = 5, nums[4] = 1, 5 > 2 * 1


Constraints:

1 <= nums.length <= 5 * 10^4
-2^31 <= nums[i] <= 2^31 - 1

*/

#include <iostream>
#include <vector>

using namespace std;

struct TreeNode {
  int val;
  int count;
  TreeNode *left;
  TreeNode *right;
  TreeNode(int x) : val(x), left(nullptr), right(nullptr), count(1) {}
};

void clear(TreeNode *r) {
  if (r == nullptr)
    return;
  clear(r->left);
  clear(r->right);
  delete r;
}

void insert(TreeNode *r, int val) {
  if (val == r->val) {
    r->count++;
    return;
  }
  if (val < r->val) {
    r->count++;
    if (r->left == nullptr) {
      r->left = new TreeNode(val);
    } else {
      insert(r->left, val);
    }
  } else {
    if (r->right == nullptr) {
      r->right = new TreeNode(val);
    } else {
      insert(r->right, val);
    }
  }
}

int visit(TreeNode *r, int val) {
  if (r == nullptr)
    return 0;
  int ans = 0;
  if (val > 2 * r->val) {
    ans = r->count + visit(r->right, val);
  } else {
    ans = visit(r->left, val);
  }
  return ans;
}

int reversePairs(const vector<int> &nums) {
  int n = nums.size(), ans = 0;
  TreeNode *root = new TreeNode(nums[n - 1]);
  for (int i = n - 2; i >= 0; i--) {
    ans += visit(root, nums[i]);
    insert(root, nums[i]);
  }
  clear(root);
  return ans;
}

int main() {
  cout << reversePairs({1, 3, 2, 3, 1}) << endl;
  cout << reversePairs({2, 4, 3, 5, 1}) << endl;
  return 0;
}
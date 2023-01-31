/*
Given an integer array nums, return an integer array counts where counts[i] is the number of smaller elements to the right of nums[i].

Example 1:

Input: nums = [5,2,6,1]
Output: [2,1,1,0]
Explanation:
To the right of 5 there are 2 smaller elements (2 and 1).
To the right of 2 there is only 1 smaller element (1).
To the right of 6 there is 1 smaller element (1).
To the right of 1 there is 0 smaller element.

Example 2:

Input: nums = [-1]
Output: [0]

Example 3:

Input: nums = [-1,-1]
Output: [0,0]


Constraints:

1 <= nums.length <= 10^5
-10^4 <= nums[i] <= 10^4
*/

#include <iostream>
#include <vector>
using namespace std;

struct TreeNode {
  int val;
  TreeNode *left, *right;
  int count;    // how many nodes as/under my left child
  int equals;   // how many nodes equal to me (including myself)
  TreeNode(int v): val(v), left(nullptr), right(nullptr), count(0), equals(1) {}
};

int insert(TreeNode* root, int num) {
  if (root == nullptr)
    return 0;

  if (num > root->val) {
    if (root->right == nullptr) {
      root->right = new TreeNode(num);
      return root->count + root->equals;
    }
    return root->count + root->equals + insert(root->right, num);
  }

  if (num < root->val) {
    root->count++;
    if (root->left == nullptr) {
      root->left = new TreeNode(num);
      return 0;
    }
    return insert(root->left, num);
  }

  root->equals++;
  return root->count;
}

void clear(TreeNode*root) {
  if (root == nullptr)
    return;
  clear(root->left);
  clear(root->right);
  delete root;
}

vector<int> countSmaller(const vector<int>& nums) {
  if (nums.empty())
    return {};
  int siz = nums.size();
  vector<int> res(siz);
  TreeNode* root = new TreeNode(nums[siz - 1]);
  res[siz - 1] = 0;

  for(int i = siz - 2; i >= 0; i--) {
    res[i] = insert(root, nums[i]);
  }

  clear(root);
  return res;
}

int main() {
  auto r = countSmaller({5,2,2,1});
  for(auto i: r)
    cout << i << " ";
  cout << endl;

  r = countSmaller({5,2,6,1});
  for(auto i: r)
    cout << i << " ";
  cout << endl;

  r = countSmaller({-1});
  for(auto i: r)
    cout << i << " ";
  cout << endl;

  r = countSmaller({-1, -1});
  for(auto i: r)
    cout << i << " ";
  cout << endl;
  return 0;
}
